#include "Systems/SpriteSystem.hpp"
#include "Game.hpp"

void SpriteSystem::Update(Game& g, entt::registry& reg) {}

void SpriteSystem::Render(Game& g, entt::registry& reg)
{
	auto view = reg.view<SpriteComponent, TransformComponent>();
	view.each([&](auto& sr, auto& t) {
		sf::CircleShape circle = sf::CircleShape(t.scale.x);
		circle.setPosition(t.position);
		circle.setFillColor(sr.color);

		sf::RectangleShape rectangle = sf::RectangleShape(t.scale);
		rectangle.setPosition(t.position);
		rectangle.setFillColor(sr.color);
		switch (sr.shape) {
		case CIRCLE:
			g.GetRenderTarget()->draw(circle);
			break;
		case RECTANGLE:
			g.GetRenderTarget()->draw(rectangle);
			break;
		}
	});
}
