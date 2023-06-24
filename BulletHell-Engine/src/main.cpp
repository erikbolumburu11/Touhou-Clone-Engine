#include "Game.hpp"
#include <Components/Components.hpp>

int main() {
	Game game(1270, 780);
	Entity player = game.CreateEntity();
	game.GetRegistry().sprites[player] = SpriteComponent();
	game.GetRegistry().transforms[player] = TransformComponent{ {300, 300}, {10, 10} };
	game.GetRegistry().velocities[player] = VelocityComponent{ {0, 0} };
	game.GetRegistry().playerMovements[player] = PlayerMovementComponent{ 300 };
	game.Run();

	ImGui::SFML::Shutdown();
	return 0;
}