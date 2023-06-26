#include "BulletHandler.hpp"
#include "Game.hpp"

Entity BulletHandler::CreateBullet(Game& game, Entity& be, sf::Vector2f direction)
{
	Entity e = game.CreateEntity();
	game.GetRegistry().bullets[e] = BulletComponent {
		game.GetBulletHandler().bullets[game.GetRegistry().bulletEmitters[be].bulletDataIndex],
		direction
	};
	game.GetRegistry().sprites[e] = SpriteComponent {
		game.GetRegistry().bullets[e].bullet.states[0].color,
		CIRCLE
	};
	game.GetRegistry().transforms[e] = TransformComponent{
		game.GetRegistry().transforms[be].position - (game.GetRegistry().bullets[e].bullet.states[0].scale - (game.GetRegistry().transforms[be].scale / 2.f)),
		game.GetRegistry().bullets[e].bullet.states[0].scale,
	};
	game.GetRegistry().velocities[e] = VelocityComponent {
		direction * game.GetRegistry().bullets[e].bullet.states[0].speed
	};

	return e;
}
