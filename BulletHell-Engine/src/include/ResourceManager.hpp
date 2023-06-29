#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#define BULLET_SPRITE_SCALE_PX 32
#define BULLET_SPRITE_MAX_COUNT 32

class ResourceManager {
public:

	///////////////////
	///// Textures ////
	///////////////////
	std::unordered_map<std::string, sf::Texture> textures;
	sf::RenderTexture bulletTextureMap;

	void Update();

	sf::Texture& GetTexture(std::string filePath);

	void BulletMapDraw(sf::Texture& tex, int index);
	void BulletMapDraw(std::string texPath, int index);

	sf::RenderTexture* GetBulletTextureMap() { return &bulletTextureMap; }
	
	ResourceManager() {
		if (!bulletTextureMap.create(sf::Vector2u(BULLET_SPRITE_MAX_COUNT * BULLET_SPRITE_SCALE_PX, BULLET_SPRITE_SCALE_PX))) {
			std::cout << "Failed to create bullet sprite map\n";
		}
	}
};
