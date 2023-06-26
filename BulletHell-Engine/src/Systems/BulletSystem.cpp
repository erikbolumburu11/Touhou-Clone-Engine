#include <iostream>
#include <Game.hpp>
#include "Systems/BulletSystem.hpp"

void BulletSystem::Update(Entity& e, Game& game)
{
	Registry& reg = game.GetRegistry();
	if (reg.bullets.contains(e)) {
		// Calculate Angular Velocity
		float av = reg.bullets[e].bullet.states[reg.bullets[e].bullet.currentState].angularVelocity;
		reg.velocities[e].velocity = reg.velocities[e].velocity.rotatedBy(sf::radians(av * game.GetDeltaTime().asSeconds()));

		//Check If Off Screen
		sf::View v = game.GetRenderTarget()->getView();
		sf::FloatRect cullRect = sf::FloatRect(
			sf::Vector2f(v.getCenter().x - v.getSize().x / 2, v.getCenter().y - v.getSize().y / 2),
			v.getSize()
		);

		TransformComponent tc = reg.transforms[e];
		sf::FloatRect bounds(tc.position, tc.scale);

		if (!(bool)bounds.findIntersection(cullRect)) {
			game.DestroyEntity(e);
		}
	}
}
