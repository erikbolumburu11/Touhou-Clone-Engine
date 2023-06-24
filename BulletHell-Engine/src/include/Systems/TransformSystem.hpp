#pragma once
#include "Components/Registry.hpp"

struct TransformSystem {
	void Update(Entity& e, float dt, Registry& reg);
};