#include "Game.hpp"
#include <Components/Components.hpp>

int main() {
	Game game(1270, 780);

	// Create Test Player
	Entity player = game.CreateEntity();
	Registry& reg = game.GetRegistry();
	reg.sprites[player] = SpriteComponent{ sf::Color::White, CIRCLE };
	reg.transforms[player] = TransformComponent{ {0, 0}, {5, 5} };
	reg.velocities[player] = VelocityComponent{ {0, 0} };
	reg.playerMovements[player] = PlayerMovementComponent{ 300 };
	
	// Create Test Emitter
	Entity emitter = game.CreateEntity();
	reg.bulletEmitters[emitter] = BulletEmitterComponent{
		0,
		STRAIGHT_SHOT,
		sf::Clock(),
		3,
		1
	};
	reg.transforms[emitter] = TransformComponent{ {0, -150 }, {20, 20} };
	reg.sprites[emitter] = SpriteComponent{ sf::Color::White, RECTANGLE};
	reg.names[emitter] = NameComponent{ "Test Emitter 1" };


	game.Run();

	ImGui::SFML::Shutdown();
	return 0;
}