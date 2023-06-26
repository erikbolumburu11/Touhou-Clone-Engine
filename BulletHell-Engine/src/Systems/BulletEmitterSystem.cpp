#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Systems/BulletEmitterSystem.hpp"
#include <Game.hpp>


void BulletEmitterSystem::Update(Entity& e, Game& game)
{
	Registry& reg = game.GetRegistry();
	if (reg.bulletEmitters.contains(e)) {
		BulletEmitterComponent& be = reg.bulletEmitters[e];
		if (be.timeSinceShot.getElapsedTime().asSeconds() >= be.fireRate) {
			be.timeSinceShot.restart();
			switch (reg.bulletEmitters[e].fireType) {
			case STRAIGHT_SHOT:
				StraightShot(e, game);
				break;
			case RADIAL_SHOT:
				RadialShot(e, game, be);
				break;
			case CONE_SHOT:
				std::cout << "Cone Shot Fired\n";
				break;
			}
		}
	}
}

void BulletEmitterSystem::StraightShot(Entity& e, Game& game)
{
	Entity b = game.GetBulletHandler().CreateBullet(game, e, { 0, 1 } );
}

void BulletEmitterSystem::RadialShot(Entity& e, Game& game, BulletEmitterComponent be)
{
	for (uint16_t i = 0; i < be.bulletsFired; i++)
	{
		float step = 2 * M_PI / be.bulletsFired;
		for (uint32_t i = 0; i < be.bulletsFired; i++)
		{
			float xDir = cos(step * i);
			float yDir = sin(step * i);
			Entity b = game.GetBulletHandler().CreateBullet(game, e, { xDir, yDir } );
		}
	}
}
