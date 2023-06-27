#pragma once
#include <entt/entt.hpp>
#include <Components/Components.hpp>

class Game;

struct BulletEmitterSystem {
	void Update(Game& game);
	void StraightShot(Game& game, const entt::registry& reg, const BulletEmitterComponent& bec);
	void RadialShot(Game& game, entt::registry& reg, BulletEmitterComponent& bec);
	void ConeShot(Game& game, entt::registry& reg, BulletEmitterComponent& bec);
};
