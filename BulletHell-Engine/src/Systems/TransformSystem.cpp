#include <Components/Components.hpp>
#include <Game.hpp>
#include "Systems/TransformSystem.hpp"

void TransformSystem::Update(Game& game, entt::registry& reg)
{
	auto view = reg.view<TransformComponent, VelocityComponent>();
	view.each([&](auto& tc, auto& vc) {
		tc.position += vc.velocity * game.GetDeltaTime().asSeconds();
	});
}
