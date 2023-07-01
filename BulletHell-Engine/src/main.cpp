#include "Game.hpp"
#include <Components/Components.hpp>

int main() {
	Game game(1500, 1000);

	entt::registry& reg = game.GetRegistry();

	entt::entity playerHitbox = reg.create();
	reg.emplace<SpriteComponent>(playerHitbox, game.GetResourceManager().GetTexture("res/PlayerHitbox.png"),
		sf::Color::White, 10001);
	reg.emplace<TransformComponent>(playerHitbox, sf::Vector2f(0, 0), sf::Vector2f(8,8) );
	reg.emplace<VelocityComponent>(playerHitbox, sf::Vector2f(0, 0) );
	reg.emplace<PlayerMovementComponent>(playerHitbox, (float)200, (float)100 );

	// Create Test Player
	entt::entity player = reg.create();
	reg.emplace<SpriteComponent>(player, game.GetResourceManager().GetTexture("res/Characters/Player1.png"),
		sf::Color::White, 10001);
	reg.emplace<TransformComponent>(player, sf::Vector2f(0, 0), sf::Vector2f(64, 64) );
	reg.emplace<VelocityComponent>(player, sf::Vector2f(0, 0) );
	reg.emplace<PlayerMovementComponent>(player, (float)200, (float)100 );


	// Create Test Emitter
	entt::entity emitter = reg.create();
	reg.emplace<BulletEmitterComponent>(emitter);
	reg.emplace<TransformComponent>(emitter, sf::Vector2f(0, -150), sf::Vector2f(64, 64));
	reg.emplace<SpriteComponent>(emitter, game.GetResourceManager().GetTexture("res/Characters/Enemy1.png"),
		sf::Color::White, 10000);
	reg.emplace<NameComponent>(emitter, "Test Emitter 1");

	game.Run();

	ImGui::SFML::Shutdown();
	return 0;
}
