#pragma once
#include "Components/Registry.hpp"

struct PlayerMovementSystem {
	void Update(Entity& e, Registry& reg);
};