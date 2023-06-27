#pragma once
#include <entt/entt.hpp>
#include <vector>
#include <BulletData.hpp>

using Entity = std::size_t;

class Game;
struct BulletHandler {
	std::vector<BulletData> bullets;

	entt::entity CreateBullet(Game& game, entt::entity& bec, sf::Vector2f direction);

	BulletHandler() {
		bullets.push_back(BulletData());
	}
};