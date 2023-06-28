#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Systems/BulletEmitterSystem.hpp"
#include <Game.hpp>


void BulletEmitterSystem::Update(Game& game)
{
	entt::registry& reg = game.GetRegistry();
	auto view = reg.view<BulletEmitterComponent, TransformComponent>();
	view.each([&](BulletEmitterComponent& bec, TransformComponent& tc) {
		entt::entity e = entt::to_entity(reg, bec);
		AttackState& as = bec.states[bec.currentState];
		std::vector<AttackPattern>& aps = as.attackPatterns;
		for (uint16_t i = 0; i < aps.size(); i++)
		{
			AttackPattern& ap = aps[i];
			ap.currentRotationRadians += ap.rotationSpeed * game.GetDeltaTime().asSeconds();
			if (ap.timeSinceShot.getElapsedTime().asSeconds() >= ap.fireRate) {
				ap.timeSinceShot.restart();
				switch (ap.fireType) {
				case STRAIGHT_SHOT:
					StraightShot(game, reg, ap, e);
					break;
				case RADIAL_SHOT:
					RadialShot(game, reg, ap, e);
					break;
				case CONE_SHOT:
					ConeShot(game, reg, ap, e);
					break;
				}
			}
		}
	});
}

void BulletEmitterSystem::StraightShot(Game& game, entt::registry& reg, AttackPattern& ap, entt::entity& e)
{
	sf::Vector2f dir(cos(ap.currentRotationRadians), sin(ap.currentRotationRadians));
	dir = dir.rotatedBy(sf::degrees(90));
	entt::entity b = game.GetBulletHandler().CreateBullet(game, e, ap, dir);
}

void BulletEmitterSystem::RadialShot(Game& game, entt::registry& reg, AttackPattern& ap, entt::entity& e)
{
	for (uint16_t i = 0; i < ap.bulletsFired; i++)
	{
		float step = 2 * M_PI / ap.bulletsFired;
		for (uint32_t i = 0; i < ap.bulletsFired; i++)
		{
			sf::Vector2f dir(cos((step * i)), sin(step * i));
			dir = dir.normalized();
			dir = dir.rotatedBy(sf::radians(ap.currentRotationRadians));
			entt::entity b = game.GetBulletHandler().CreateBullet(game, e, ap, dir);
		}
	}
}

void BulletEmitterSystem::ConeShot(Game& game, entt::registry& reg, AttackPattern& ap, entt::entity& e)
{
	for (uint16_t i = 0; i < ap.bulletsFired; i++)
	{
		float step = 2 * M_PI / ap.bulletsFired;
		for (uint32_t i = 0; i < ap.bulletsFired; i++)
		{
			sf::Vector2f dir(cos(step * i + ap.currentRotationRadians), sin(step * i + ap.currentRotationRadians));
			dir = dir.normalized();
			entt::entity b = game.GetBulletHandler().CreateBullet(game, e, ap, dir);
		}
	}
}
