#pragma once
#include <string>
#include <imgui.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <ResourceManager.hpp>

struct BulletState {
public:
	std::string name = "New State";
	float speed = 300;
	ImVec4 color = sf::Color::Red;
	sf::Texture* texture;
	float scale = 17;
	
	int drawLayer = 0;
	float angularVelocity = 0;

	BulletState(ResourceManager& rm) : texture(rm.GetTexture("res/Bullets/SmallCircle.png")) {}

private:
	BulletState& operator=(const BulletState&) = delete;
};

class Game;
struct BulletData {
public:
	std::string name = "New Bullet";
	std::vector<BulletState> states;
	uint32_t currentState = 0;

	BulletData(ResourceManager& rm) {
		states.push_back(BulletState(rm));
	}

private:
	BulletData& operator=(const BulletData&) = delete;
};