#include <iostream>
#include <Game.hpp>
#include "Systems/BulletSystem.hpp"

void BulletSystem::Update(Game& game)
{
	auto view = game.GetRegistry().view<BulletComponent, VelocityComponent, TransformComponent>();
	view.each([&](auto& bc, auto& vc, auto& tc) {
		// Calculate Angular Velocity
		float av = bc.bullet.states[bc.bullet.currentState].angularVelocity;
		vc.velocity = vc.velocity.rotatedBy(sf::radians(av * game.GetDeltaTime().asSeconds()));

		//Check If Off Screen
		sf::View v = game.GetRenderTarget()->getView();
		sf::FloatRect cullRect = sf::FloatRect(
			sf::Vector2f(v.getCenter().x - v.getSize().x / 2, v.getCenter().y - v.getSize().y / 2),
			v.getSize()
		);

		sf::FloatRect bounds(tc.position, tc.scale);

		if (!(bool)bounds.findIntersection(cullRect)) {
			entt::entity e = entt::to_entity(game.GetRegistry(), bc);
			game.GetRegistry().destroy(e);
		}
	});
}
