#include "Systems/PlayerMovementSystem.hpp"

void PlayerMovementSystem::Update(Entity& e, Registry& reg)
{
	if (reg.playerMovements.contains(e) && reg.velocities.contains(e)) {
		float speed = reg.playerMovements[e].movementSpeed;
		reg.velocities[e].velocity = { 0, 0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) reg.velocities[e].velocity.y += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) reg.velocities[e].velocity.y -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) reg.velocities[e].velocity.x += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) reg.velocities[e].velocity.x -= speed;
	}
}
