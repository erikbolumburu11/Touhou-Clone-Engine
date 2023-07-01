#pragma once
#include <entt/entt.hpp>
#include <vector>
#include <Attack.hpp>
#include <BulletData.hpp>

using Entity = std::size_t;

class Game;
struct BulletHandler {
	std::vector<BulletData> bullets;

	entt::entity CreateBullet(Game& game, entt::entity& be, AttackPattern& ap, sf::Vector2f direction);

	void ClearBullets(Game& game);

	BulletHandler(ResourceManager& rm) {
		bullets.push_back(BulletData(rm));
	}
};