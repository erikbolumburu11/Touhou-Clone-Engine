#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Systems/BulletEmitterSystem.hpp"
#include <Game.hpp>


void BulletEmitterSystem::Update(Entity& e, Game& game)
{
	Registry& reg = game.GetRegistry();
	if (reg.bulletEmitters.contains(e)) {
		reg.bulletEmitters[e].currentRotationRadians += reg.bulletEmitters[e].rotationSpeed * game.GetDeltaTime().asSeconds();
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
	Registry& reg = game.GetRegistry();
	sf::Vector2f dir(cos(reg.bulletEmitters[e].currentRotationRadians), sin(reg.bulletEmitters[e].currentRotationRadians));
	Entity b = game.GetBulletHandler().CreateBullet(game, e, dir);
}

void BulletEmitterSystem::RadialShot(Entity& e, Game& game, BulletEmitterComponent be)
{
	Registry& reg = game.GetRegistry();
	for (uint16_t i = 0; i < be.bulletsFired; i++)
	{
		float step = 2 * M_PI / be.bulletsFired;
		for (uint32_t i = 0; i < be.bulletsFired; i++)
		{
			sf::Vector2f dir(cos((step * i)), sin(step * i));
			dir = dir.normalized();
			dir = dir.rotatedBy(sf::radians(be.currentRotationRadians));
			Entity b = game.GetBulletHandler().CreateBullet(game, e, dir);
		}
	}
}

void BulletEmitterSystem::ConeShot(Entity& e, Game& game, BulletEmitterComponent be)
{
	Registry& reg = game.GetRegistry();
	for (uint16_t i = 0; i < be.bulletsFired; i++)
	{
		float step = 2 * M_PI / be.bulletsFired;
		for (uint32_t i = 0; i < be.bulletsFired; i++)
		{
			sf::Vector2f dir(cos((step * i) + be.currentRotationRadians), sin(step * i) + be.currentRotationRadians);
			dir = dir.normalized();
			Entity b = game.GetBulletHandler().CreateBullet(game, e, dir);
		}
	}
}
