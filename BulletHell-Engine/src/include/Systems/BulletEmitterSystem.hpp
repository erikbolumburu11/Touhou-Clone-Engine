#pragma once
#include <entt/entt.hpp>
#include <Attack.hpp>
#include <Components/Components.hpp>

class Game;

struct BulletEmitterSystem {
	void Update(Game& game);
	void StraightShot(Game& game, entt::registry& reg, AttackPattern& ap, entt::entity& e);
	void RadialShot(Game& game, entt::registry& reg, AttackPattern& ap, entt::entity& e);
	void ConeShot(Game& game, entt::registry& reg, AttackPattern& ap, entt::entity& e);
};
