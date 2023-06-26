#pragma once 
#include <SFML/Graphics.hpp>
#include <BulletData.hpp>
#include "FireTypes.hpp"

enum SpriteShapes {
	CIRCLE,
	RECTANGLE
};

struct SpriteComponent {
	sf::Color color;
	SpriteShapes shape;
};

struct VelocityComponent {
	sf::Vector2f velocity;
};

struct TransformComponent {
	sf::Vector2f position;
	sf::Vector2f scale;
};

struct PlayerMovementComponent {
	float movementSpeed;
};

struct BulletEmitterComponent {
	uint32_t bulletDataIndex;			// Bullet To be shot
	FireTypes fireType;
	sf::Clock timeSinceShot;
	int bulletsFired;			// Fire X bullets every shot
	float fireRate;				// Fire every X seconds
};

struct BulletComponent {
	BulletData bullet;
	sf::Vector2f angle;
};

struct NameComponent {
	std::string name;
};
