#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <magic_enum_all.hpp>
#include <Menus/EditorBase.hpp>
#include "Game.hpp"

class EmitterEditor : public EditorBase {
public:
	std::string label;
	std::vector<Entity> entities;
	
	virtual void Update(Game& game) override {
		ImGui::Begin("Emitter Editor");

		Registry& reg = game.GetRegistry();
		static Entity selectedEmitterIndex = reg.bulletEmitters.begin()->first;{};
		entities.clear();

		// SELECT EMITTER
		if (reg.bulletEmitters.empty()) {
			ImGui::TextColored(ImVec4(sf::Color::Red), "No Emitters In Scene!");
		}
		else {
			for (auto& bulletEmitter : reg.bulletEmitters) {
				entities.push_back(bulletEmitter.first);
				if (bulletEmitter.first == selectedEmitterIndex) {
					Entity e = bulletEmitter.first;
					BulletEmitterComponent& be = bulletEmitter.second;

					selectedEmitterIndex = e;

					if (reg.names.contains(e)) {
						label = reg.names[e].name + "###init";
					}
				}
			}

			if (!entities.empty()) {
				if (ImGui::BeginCombo("##label2", label.c_str())) {
					for (Entity e = 0; e <= entities.size(); e++) {
						if (reg.names.contains(e) && reg.bulletEmitters.contains(e)) {
							std::string name = reg.names[e].name + "###" + std::to_string(e);
							bool isSelected = (e == selectedEmitterIndex);
							if (ImGui::Selectable(name.c_str(), isSelected)) {
								selectedEmitterIndex = e;
							}
						}
					}
					ImGui::EndCombo();
				}
			}
			std::string timeSinceShot = "Time Since Last Shot: " + std::to_string(reg.bulletEmitters[selectedEmitterIndex].timeSinceShot.getElapsedTime().asSeconds());
			ImGui::Text(timeSinceShot.c_str());

			// CHANGE NAME
			ImGui::InputText("Name", &reg.names[selectedEmitterIndex].name);

			static uint32_t bulletSelectIndex = 0;
			BulletHandler& bh = game.GetBulletHandler();

			// SELECT BULLETDATA
			if (!bh.bullets.empty()) {
				if (ImGui::BeginCombo("Select Bullet Data", bh.bullets[bulletSelectIndex].name.c_str())) {
					for (uint32_t i = 0; i < bh.bullets.size(); i++)
					{
						bool isSelected = &bh.bullets[i] == &bh.bullets[bulletSelectIndex];
						std::string label = bh.bullets[i].name + "###" + std::to_string(i); // Avoid label conflicts
						if (ImGui::Selectable(label.c_str(), isSelected)) {
							bulletSelectIndex = i;
							reg.bulletEmitters[selectedEmitterIndex].bulletDataIndex = bulletSelectIndex;
						}
					}
					ImGui::EndCombo();
				}
			}
			else {
				ImGui::TextColored(ImVec4(sf::Color::Red), "No Bullet Data!");
			}

			// SET AMOUNT OF BULLETS FIRED PER SHOT
			ImGui::InputInt("Bullet Count", &reg.bulletEmitters[selectedEmitterIndex].bulletsFired);

			// SET FIRE RATE
			ImGui::InputFloat("Fire Rate", &reg.bulletEmitters[selectedEmitterIndex].fireRate);

			// SET FIRE TYPE
			if (ImGui::BeginCombo("Select Fire Type", magic_enum::enum_name(reg.bulletEmitters[selectedEmitterIndex].fireType).data())) {
				for (uint16_t i = 0; i < magic_enum::enum_count<FireTypes>(); i++)
				{
					std::string enumName = magic_enum::enum_name(magic_enum::enum_value<FireTypes>(i)).data();
					uint16_t enumInt = magic_enum::enum_integer(magic_enum::enum_value<FireTypes>(i));

					bool isSelected = enumInt == magic_enum::enum_integer(reg.bulletEmitters[selectedEmitterIndex].fireType);
					std::string label = enumName + "###" + std::to_string(enumInt); // Avoid label conflicts
					if (ImGui::Selectable(label.c_str(), isSelected)) {
						reg.bulletEmitters[selectedEmitterIndex].fireType = magic_enum::enum_value<FireTypes>(i);
					}
				};
				ImGui::EndCombo();
			}

		}

		ImGui::End();
	}

	const char* GetName() {
		return "Emitter Editor";
	}
};
