#include "Systems/SpriteSystem.hpp"
#include "Game.hpp"

void SpriteSystem::Update(Entity& e, Game& g, Registry& reg) {}

void SpriteSystem::Render(Entity& e, Game& g, Registry& reg)
{
	if (reg.sprites.contains(e) && reg.transforms.contains(e)) {
		sf::CircleShape circle = sf::CircleShape(reg.transforms[e].scale.x);
		circle.setPosition(reg.transforms[e].position);
		circle.setFillColor(reg.sprites[e].color);

		sf::RectangleShape rectangle = sf::RectangleShape(reg.transforms[e].scale);
		rectangle.setPosition(reg.transforms[e].position);
		rectangle.setFillColor(reg.sprites[e].color);
		switch (reg.sprites[e].shape) {
		case CIRCLE:
			g.GetRenderTarget()->draw(circle);
			break;
		case RECTANGLE:
			g.GetRenderTarget()->draw(rectangle);
			break;
		}
	}
}
