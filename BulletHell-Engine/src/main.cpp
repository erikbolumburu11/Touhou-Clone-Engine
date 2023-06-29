#include "Game.hpp"
#include <Components/Components.hpp>

int main() {
	Game game(1500, 1000);

	// Create Test Player
	entt::registry& reg = game.GetRegistry();
	entt::entity player = reg.create();
	reg.emplace<SpriteComponent>(player, game.GetResourceManager().GetTexture("res/Characters/Player1.png"),
		sf::Color::White, 10001);
	reg.emplace<TransformComponent>(player, sf::Vector2f(0, 0), sf::Vector2f(64, 64) );
	reg.emplace<VelocityComponent>(player, sf::Vector2f(0, 0) );
	reg.emplace<PlayerMovementComponent>(player, (float)300, (float)200 );

	// Create Test Emitter
	entt::entity emitter = reg.create();
	reg.emplace<BulletEmitterComponent>(emitter);
	reg.emplace<TransformComponent>(emitter, sf::Vector2f(0, -150), sf::Vector2f(64, 64));
	reg.emplace<SpriteComponent>(emitter, game.GetResourceManager().GetTexture("res/Characters/Enemy1.png"),
		sf::Color::White, 10000);
	reg.emplace<NameComponent>(emitter, "Test Emitter 1");

	game.GetResourceManager().BulletMapDraw("res/Bullets/SmallCircle.png", 0);
	game.GetResourceManager().BulletMapDraw("res/Bullets/ArrowHead.png", 1);

	game.Run();

	ImGui::SFML::Shutdown();
	return 0;
}
