#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Systems/BulletEmitterSystem.hpp"
#include <Game.hpp>


void BulletEmitterSystem::Update(Game& game)
{
	entt::registry& reg = game.GetRegistry();
	auto view = reg.view<BulletEmitterComponent, TransformComponent>();
	view.each([&](auto& bec, auto& tc) {
		bec.currentRotationRadians += bec.rotationSpeed * game.GetDeltaTime().asSeconds();
		if (bec.timeSinceShot.getElapsedTime().asSeconds() >= bec.fireRate) {
			bec.timeSinceShot.restart();
			switch (bec.fireType) {
			case STRAIGHT_SHOT:
				StraightShot(game, reg, bec);
				break;
			case RADIAL_SHOT:
				RadialShot(game, reg, bec);
				break;
			case CONE_SHOT:
				std::cout << "Cone Shot Fired\n";
				break;
			}
		}
	});
}

void BulletEmitterSystem::StraightShot(Game& game, const entt::registry& reg, const BulletEmitterComponent& bec)
{
	sf::Vector2f dir(cos(bec.currentRotationRadians), sin(bec.currentRotationRadians));
	entt::entity e = entt::to_entity(reg, bec);
	entt::entity b = game.GetBulletHandler().CreateBullet(game, e, dir);
}

void BulletEmitterSystem::RadialShot(Game& game, entt::registry& reg, BulletEmitterComponent& bec)
{
	for (uint16_t i = 0; i < bec.bulletsFired; i++)
	{
		float step = 2 * M_PI / bec.bulletsFired;
		for (uint32_t i = 0; i < bec.bulletsFired; i++)
		{
			sf::Vector2f dir(cos((step * i)), sin(step * i));
			dir = dir.normalized();
			dir = dir.rotatedBy(sf::radians(bec.currentRotationRadians));
			entt::entity e = entt::to_entity(reg, bec);
			entt::entity b = game.GetBulletHandler().CreateBullet(game, e, dir);
		}
	}
}

void BulletEmitterSystem::ConeShot(Game& game, entt::registry& reg, BulletEmitterComponent& bec)
{
	for (uint16_t i = 0; i < bec.bulletsFired; i++)
	{
		float step = 2 * M_PI / bec.bulletsFired;
		for (uint32_t i = 0; i < bec.bulletsFired; i++)
		{
			sf::Vector2f dir(cos((step * i) + bec.currentRotationRadians), sin(step * i) + bec.currentRotationRadians);
			dir = dir.normalized();
			entt::entity e = entt::to_entity(reg, bec);
			entt::entity b = game.GetBulletHandler().CreateBullet(game, e, dir);
		}
	}
}
