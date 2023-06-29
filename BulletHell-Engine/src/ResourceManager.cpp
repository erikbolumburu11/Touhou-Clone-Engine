#include "ResourceManager.hpp"

void ResourceManager::Update()
{
	bulletTextureMap.display();
}

sf::Texture& ResourceManager::GetTexture(std::string filePath)
{
	if (textures.contains(filePath)) {
		return textures[filePath];
	}

	sf::Texture tex = sf::Texture();
	if (!tex.loadFromFile(filePath)) {
		std::cout << "Error" << std::endl;
	}
	textures[filePath] = tex;
	return textures[filePath];
}

void ResourceManager::BulletMapDraw(sf::Texture& tex, int index)
{
	sf::RectangleShape r({ BULLET_SPRITE_SCALE_PX, BULLET_SPRITE_SCALE_PX });
	r.setPosition({ (float)index * BULLET_SPRITE_SCALE_PX, 0 });
	r.setTexture(&tex);
	bulletTextureMap.draw(r);
}

void ResourceManager::BulletMapDraw(std::string texPath, int index)
{
	sf::Texture& tex = GetTexture(texPath);
	BulletMapDraw(tex, index);
}
