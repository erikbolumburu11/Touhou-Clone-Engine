#pragma once 
#include <iostream>
#include <unordered_map>
#include "Components/Registry.hpp"

class Game;

struct SpriteSystem {
	void Update(Entity& e, Game& g, Registry& reg);
	void Render(Entity& e, Game& g, Registry& reg);
};
