#include "Systems/TransformSystem.hpp"

class Game;

void TransformSystem::Update(Entity& e, float dt, Registry& reg)
{
	if (reg.transforms.contains(e) && reg.velocities.contains(e)) {
		reg.transforms[e].position += reg.velocities[e].velocity * dt;
	}
}
