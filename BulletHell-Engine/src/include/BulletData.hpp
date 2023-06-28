#pragma once
#include <string>
#include <imgui.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

struct BulletState {
	std::string name = "New State";
	float speed = 300;
	ImVec4 color = sf::Color::Red;
	sf::Vector2f scale = { 10, 10 };
	int drawLayer = 0;
	float angularVelocity = 0;
};

struct BulletData {
	std::string name = "New Bullet";
	std::vector<BulletState> states;
	uint32_t currentState = 0;

	BulletData() {
		states.push_back(BulletState());
	}
};