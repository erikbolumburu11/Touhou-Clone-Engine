#pragma once 
#include <SFML/Graphics.hpp>
#include <BulletData.hpp>
#include "FireTypes.hpp"
#include <Attack.hpp>

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
	float shiftMovementSpeed;
};

struct BulletEmitterComponent {
	int currentState = 0;
	std::vector<AttackState> states;

	BulletEmitterComponent(){
		states.push_back(AttackState());
	}
};

struct BulletComponent {
	BulletData bullet;
	sf::Vector2f angle;
};

struct NameComponent {
	std::string name;
};
