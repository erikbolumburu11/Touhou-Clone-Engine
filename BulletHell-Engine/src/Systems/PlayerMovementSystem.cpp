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
		sf::Vector2<float> v(0.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) v.y += 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) v.y -= 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) v.x += 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) v.x -= 1.f;
		if(v.x != 0.f || v.y != 0.f) v = v.normalized();
		vc.velocity = v * speed;
	});
}
