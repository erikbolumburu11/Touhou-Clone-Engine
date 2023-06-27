#include "Systems/PlayerMovementSystem.hpp"
#include <Components/components.hpp>

void PlayerMovementSystem::Update(entt::registry& reg)
{
	auto view = reg.view<PlayerMovementComponent, VelocityComponent>();
	view.each([&](auto& pmc, auto& vc) {
		float speed;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) speed = pmc.movementSpeed;
		else speed = pmc.shiftMovementSpeed;
		vc.velocity = { 0, 0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) vc.velocity.y += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) vc.velocity.y -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) vc.velocity.x += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) vc.velocity.x -= speed;
	});
}
