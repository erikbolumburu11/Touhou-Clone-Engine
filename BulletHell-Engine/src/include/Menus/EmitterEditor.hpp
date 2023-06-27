#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <magic_enum_all.hpp>
#include <Menus/EditorBase.hpp>
#include "Game.hpp"
#include "Components/Components.hpp"

class EmitterEditor : public EditorBase {
public:
	std::string label;
	
	virtual void Update(Game& game) override {
		ImGui::Begin("Emitter Editor");

		entt::registry& reg = game.GetRegistry();

		// SELECT EMITTER
		auto bes = reg.view<BulletEmitterComponent>();
		auto emitters = reg.view<BulletEmitterComponent, NameComponent>();
		static auto first = emitters.front();
		static entt::entity selectedEmitter = first;
		if (bes.empty()) {
			ImGui::TextColored(ImVec4(sf::Color::Red), "No Emitters In Scene!");
		}
		else {
			label = reg.get<NameComponent>(first).name + "###" + std::to_string((int)first);
			if(ImGui::BeginCombo("###SelectEmitter", label.c_str())) {
				emitters.each([&](auto& be, auto& nc) {
					std::string name = nc.name + "###" + std::to_string((int)entt::to_entity(reg, nc));
					bool isSelected = (&be == &reg.get<BulletEmitterComponent>(selectedEmitter));
					if (ImGui::Selectable(name.c_str(), isSelected)) {
						entt::entity e = entt::to_entity(reg, be);
						selectedEmitter = e;
					}
				});
			}

			auto& sebec = reg.get<BulletEmitterComponent>(selectedEmitter);
			auto& sen = reg.get<NameComponent>(selectedEmitter);

			std::string timeSinceShot = "Time Since Last Shot: " + std::to_string(sebec.timeSinceShot.getElapsedTime().asSeconds());
			ImGui::Text(timeSinceShot.c_str());

			// CHANGE NAME
			ImGui::InputText("Name", &sen.name);

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
							sebec.bulletDataIndex = bulletSelectIndex;
						}
					}
					ImGui::EndCombo();
				}
			}
			else {
				ImGui::TextColored(ImVec4(sf::Color::Red), "No Bullet Data!");
			}

			// SET AMOUNT OF BULLETS FIRED PER SHOT
			ImGui::InputInt("Bullet Count", &sebec.bulletsFired);

			// SET FIRE RATE
			ImGui::InputFloat("Fire Rate", &sebec.fireRate);
			ImGui::DragFloat("Rotation Speed", &sebec.rotationSpeed, 0.01, -3, 3);

			// SET FIRE TYPE
			if (ImGui::BeginCombo("Select Fire Type", magic_enum::enum_name(sebec.fireType).data())) {
				for (uint16_t i = 0; i < magic_enum::enum_count<FireTypes>(); i++)
				{
					std::string enumName = magic_enum::enum_name(magic_enum::enum_value<FireTypes>(i)).data();
					uint16_t enumInt = magic_enum::enum_integer(magic_enum::enum_value<FireTypes>(i));

					bool isSelected = enumInt == magic_enum::enum_integer(sebec.fireType);
					std::string label = enumName + "###" + std::to_string(enumInt); // Avoid label conflicts
					if (ImGui::Selectable(label.c_str(), isSelected)) {
						sebec.fireType = magic_enum::enum_value<FireTypes>(i);
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
