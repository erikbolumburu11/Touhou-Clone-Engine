#pragma once
#include <vector>
#include <BulletData.hpp>

using Entity = std::size_t;

class Game;
struct BulletHandler {
	std::vector<BulletData> bullets;

	Entity CreateBullet(Game& game, Entity& entity, sf::Vector2f direction);

	BulletHandler() {
		bullets.push_back(BulletData());
	}
};