#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Components/FireTypes.hpp>

class Game;
struct AttackPattern {
	uint32_t bulletDataIndex;
	FireTypes fireType;
	sf::Clock timeSinceShot;
	int bulletsFired;
	float fireRate;				

	float rotationSpeed;
	float currentRotationRadians;

	AttackPattern() {
		bulletDataIndex = 0;
		fireType = STRAIGHT_SHOT;
		timeSinceShot = sf::Clock();
		bulletsFired = 1;			
		fireRate = 1;				

		rotationSpeed = 0;
		currentRotationRadians = 0;
	}
};

struct AttackState {
	std::vector<AttackPattern> attackPatterns;

	AttackState() {
		attackPatterns.push_back(AttackPattern());
	}
};
