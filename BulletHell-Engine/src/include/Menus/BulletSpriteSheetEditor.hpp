#pragma once
#include <ResourceManager.hpp>
#include <Menus/EditorBase.hpp>

class BulletSpriteSheetEditor : public EditorBase {
	
	virtual void Update(Game& game) {

		static uint16_t selectedSprite;

		ImGui::Begin("Bullet Sprite Sheet Editor");

		sf::Sprite sprite(game.GetResourceManager().GetBulletTextureMap()->getTexture());
		if (ImGui::BeginTable("Sprites", 16, ImGuiTableFlags_ScrollX)) {
			for (uint16_t i = 0; i < BULLET_SPRITE_MAX_COUNT; i++)
			{
				ImGui::TableNextColumn();
				sprite.setTextureRect(sf::IntRect(
					sf::Vector2i(i * BULLET_SPRITE_SCALE_PX, 0),
					sf::Vector2i(BULLET_SPRITE_SCALE_PX, BULLET_SPRITE_SCALE_PX)
				));
				ImGui::PushID(i);
				if (ImGui::ImageButton(sprite)) {
					std::cout << "Index: " << i << std::endl;
				}
				ImGui::PopID();
			}
			ImGui::EndTable();
		}


		//ImGui::Image(bs);

		ImGui::End();
	}

	const char* GetName() {
		return "Bullet Editor";
	}
};