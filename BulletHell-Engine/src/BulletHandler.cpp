#include "BulletHandler.hpp"
#include "Game.hpp"

entt::entity BulletHandler::CreateBullet(Game& game, entt::entity& be, AttackPattern& ap, sf::Vector2f direction)
{
	entt::registry& reg = game.GetRegistry();
	entt::entity e = reg.create();

	BulletEmitterComponent& bec = reg.get<BulletEmitterComponent>(be);
	TransformComponent& bet = reg.get<TransformComponent>(be);

	BulletData& bd = bullets[ap.bulletDataIndex];

	reg.emplace<BulletComponent>( 
		e,
		ap.bulletDataIndex,
		direction
	);

	BulletComponent& bc = reg.get<BulletComponent>(e);

	reg.emplace<SpriteComponent>(
		e,
		nullptr,
		bd.states[0].color,
		bd.states[0].drawLayer
	);
	reg.emplace<TransformComponent>(
		e,
		bet.position - (sf::Vector2f(bd.states[0].scale, bd.states[0].scale) / 2.f),
		sf::Vector2f(bd.states[0].scale, bd.states[0].scale)
	);
	reg.emplace<VelocityComponent>(
		e,
		direction * bd.states[0].speed
	);

	game.bulletCount++;

	return e;
}

void BulletHandler::ClearBullets(Game& game)
{
	auto view = game.GetRegistry().view<BulletComponent>();
	view.each([&](BulletComponent& bc) {
			entt::entity e = entt::to_entity(game.GetRegistry(), bc);
			game.GetRegistry().destroy(e);
	});
	game.bulletCount = 0;
}
