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
				ImGui::EndCombo();
			}

			auto& bulletEmitterComponent = reg.get<BulletEmitterComponent>(selectedEmitter);
			auto& nameComponent = reg.get<NameComponent>(selectedEmitter);

			// CHANGE NAME
			ImGui::InputText("Name", &nameComponent.name);

			for (uint16_t s = 0; s < bulletEmitterComponent.states.size(); s++)
			{
				std::string stateLabel = "State " + std::to_string(s);
				if (ImGui::TreeNode(stateLabel.c_str())) {
					if (ImGui::Button("New Attack Pattern")) {
						bulletEmitterComponent.states[s].attackPatterns.push_back(AttackPattern());
					}
					for (uint16_t ap = 0; ap < bulletEmitterComponent.states[s].attackPatterns.size(); ap++) {
						std::string attackPatternLabel = "Attack Pattern " + std::to_string(ap);
						if (ImGui::TreeNode(attackPatternLabel.c_str())) {
							AttackPattern& attackPattern = bulletEmitterComponent.states[s].attackPatterns[ap];
							std::string timeSinceShot = "Time Since Last Shot: " + std::to_string(attackPattern.timeSinceShot.getElapsedTime().asSeconds());
							ImGui::Text(timeSinceShot.c_str());

							BulletHandler& bh = game.GetBulletHandler();

							// SELECT BULLETDATA
							if (!bh.bullets.empty()) {
								if (ImGui::BeginCombo("Select Bullet Data", bh.bullets[bulletEmitterComponent.states[s].attackPatterns[ap].bulletDataIndex].name.c_str())) {
									for (uint32_t i = 0; i < bh.bullets.size(); i++)
									{
										bool isSelected = &bh.bullets[i] == &bh.bullets[bulletEmitterComponent.states[s].attackPatterns[ap].bulletDataIndex];
										std::string label = bh.bullets[i].name + "###" + std::to_string(i); // Avoid label conflicts
										if (ImGui::Selectable(label.c_str(), isSelected)) {
											attackPattern.bulletDataIndex = i;
										}
									}
									ImGui::EndCombo();
								}
							}
							else {
								ImGui::TextColored(ImVec4(sf::Color::Red), "No Bullet Data!");
							}

							// SET AMOUNT OF BULLETS FIRED PER SHOT
							ImGui::InputInt("Bullet Count", &attackPattern.bulletsFired);

							// SET FIRE RATE
							ImGui::InputFloat("Fire Rate", &attackPattern.fireRate);
							ImGui::DragFloat("Rotation Speed", &attackPattern.rotationSpeed, 0.01, -3, 3);

							// SET FIRE TYPE
							if (ImGui::BeginCombo("Select Fire Type", magic_enum::enum_name(attackPattern.fireType).data())) {
								for (uint16_t i = 0; i < magic_enum::enum_count<FireTypes>(); i++)
								{
									std::string enumName = magic_enum::enum_name(magic_enum::enum_value<FireTypes>(i)).data();
									uint16_t enumInt = magic_enum::enum_integer(magic_enum::enum_value<FireTypes>(i));

									bool isSelected = enumInt == magic_enum::enum_integer(attackPattern.fireType);
									std::string label = enumName + "###" + std::to_string(enumInt); // Avoid label conflicts
									if (ImGui::Selectable(label.c_str(), isSelected)) {
										attackPattern.fireType = magic_enum::enum_value<FireTypes>(i);
									}
								};
								ImGui::EndCombo();
							}
							ImGui::TreePop();
						}
					}
					ImGui::TreePop();
				}
			}

		}
		

		ImGui::End();
	}

	const char* GetName() {
		return "Emitter Editor";
	}
};
