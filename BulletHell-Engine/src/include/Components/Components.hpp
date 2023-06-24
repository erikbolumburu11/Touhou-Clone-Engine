#pragma once 
#include <SFML/Graphics.hpp>

struct SpriteComponent {
	std::shared_ptr<sf::Texture> texture;
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
