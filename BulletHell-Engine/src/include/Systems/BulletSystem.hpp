#pragma once
#include <Components/Registry.hpp>

class Game;
struct BulletSystem {
	void Update(Entity& e, Game& reg);
};