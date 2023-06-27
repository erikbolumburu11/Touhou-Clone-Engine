#include "Game.hpp"
#include <Components/Components.hpp>

int main() {
	Game game(1270, 780);

	// Create Test Player
	entt::registry& reg = game.GetRegistry();
	entt::entity player = reg.create();
	reg.emplace<SpriteComponent>(player, sf::Color::White, CIRCLE);
	reg.emplace<TransformComponent>(player, sf::Vector2f(0, 0), sf::Vector2f(5, 5) );
	reg.emplace<VelocityComponent>(player, sf::Vector2f(0, 0) );
	reg.emplace<PlayerMovementComponent>(player, (float)300, (float)150 );
	
	// Create Test Emitter
	entt::entity emitter = reg.create();
	reg.emplace<BulletEmitterComponent>(
		emitter,
		(uint32_t)0,
		STRAIGHT_SHOT,
		sf::Clock(),
		(int)3,
		(float)1,
		(float)0,
		(float)0
	);
	reg.emplace<TransformComponent>(emitter, sf::Vector2f(0, -150), sf::Vector2f(20, 20) );
	reg.emplace<SpriteComponent>(emitter, sf::Color::White, RECTANGLE);
	reg.emplace<NameComponent>(emitter, "Test Emitter 1");

	game.Run();

	ImGui::SFML::Shutdown();
	return 0;
}