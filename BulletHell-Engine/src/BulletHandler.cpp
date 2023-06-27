#include "BulletHandler.hpp"
#include "Game.hpp"

entt::entity BulletHandler::CreateBullet(Game& game, entt::entity& be, sf::Vector2f direction)
{
	entt::registry& reg = game.GetRegistry();
	entt::entity e = reg.create();

	BulletEmitterComponent bec = reg.get<BulletEmitterComponent>(be);
	TransformComponent bet = reg.get<TransformComponent>(be);

	reg.emplace<BulletComponent>( 
		e,
		game.GetBulletHandler().bullets[bec.bulletDataIndex],
		direction
	);

	BulletComponent bc = reg.get<BulletComponent>(e);

	reg.emplace<SpriteComponent>(
		e,
		bc.bullet.states[0].color,
		CIRCLE
	);
	reg.emplace<TransformComponent>(
		e,
		bet.position - (bc.bullet.states[0].scale - (bet.scale / 2.f)),
		bc.bullet.states[0].scale
	);
	reg.emplace<VelocityComponent>(
		e,
		direction * bc.bullet.states[0].speed
	);

	return e;
}
