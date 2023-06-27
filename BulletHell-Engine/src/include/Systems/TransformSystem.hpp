#pragma once
#include <entt/entt.hpp>

class Game;
struct TransformSystem {
	void Update(Game& game, entt::registry& reg);
};