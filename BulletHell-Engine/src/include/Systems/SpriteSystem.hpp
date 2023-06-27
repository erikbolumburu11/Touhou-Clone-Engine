#pragma once 
#include <iostream>
#include <unordered_map>
#include <entt/entt.hpp>

class Game;

struct SpriteSystem {
	void Update(Game& g, entt::registry& reg);
	void Render(Game& g, entt::registry& reg);
};
