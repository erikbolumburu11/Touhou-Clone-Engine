#pragma once
#include "Components/Registry.hpp"

class Game;

struct BulletEmitterSystem {
	void Update(Entity& e, Game& game);
	void StraightShot(Entity& e, Game& game);
	void RadialShot(Entity& e, Game& game, BulletEmitterComponent be);
	void ConeShot(Entity& e, Game& game, BulletEmitterComponent be);
};
