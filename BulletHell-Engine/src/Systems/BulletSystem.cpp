#include "Systems/BulletSystem.hpp"
#include <iostream>

void BulletSystem::Update(Entity& e, Registry& reg)
{
	// Calculate Angular Velocity
	if (reg.bullets.contains(e)) {
		BulletComponent& bc = reg.bullets[e];
		BulletState& bs = bc.bullet.states[reg.bullets[e].bullet.currentState];
		float angle = atan2f(bc.angle.x, bc.angle.y);
		float newAngle = angle + bs.angularVelocity;
		sf::Vector2f newAngleVec = {
			cos(newAngle),
			sin(newAngle)
		};
		bc.angle = newAngleVec;
		reg.velocities[e].velocity += newAngleVec * bs.speed;
		float x = 10;
	}
}
