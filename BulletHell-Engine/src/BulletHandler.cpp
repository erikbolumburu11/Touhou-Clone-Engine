#include "BulletHandler.hpp"
#include "Game.hpp"

entt::entity BulletHandler::CreateBullet(Game& game, entt::entity& be, AttackPattern& ap, sf::Vector2f direction)
{
	entt::registry& reg = game.GetRegistry();
	entt::entity e = reg.create();

	BulletEmitterComponent bec = reg.get<BulletEmitterComponent>(be);
	TransformComponent bet = reg.get<TransformComponent>(be);

	reg.emplace<BulletComponent>( 
		e,
		game.GetBulletHandler().bullets[ap.bulletDataIndex],
		direction
	);

	BulletComponent bc = reg.get<BulletComponent>(e);

	reg.emplace<SpriteComponent>(
		e,
		game.GetResourceManager().GetTexture(bc.bullet.states[0].texturePath),
		bc.bullet.states[0].color,
		bc.bullet.states[0].drawLayer
	);
	reg.emplace<TransformComponent>(
		e,
		bet.position + (bet.scale / 2.f),
		sf::Vector2f(bc.bullet.states[0].scale, bc.bullet.states[0].scale)
	);
	reg.emplace<VelocityComponent>(
		e,
		direction * bc.bullet.states[0].speed
	);

	return e;
}
