#include "Systems/SpriteSystem.hpp"
#include "Game.hpp"

void SpriteSystem::Update(Entity& e, Game& g, Registry& reg)
{
	if (reg.sprites.contains(e)) {
	}
}

void SpriteSystem::Render(Entity& e, Game& g, Registry& reg)
{
	if (reg.sprites.contains(e) && reg.transforms.contains(e)) {
		sf::CircleShape shape(reg.transforms[e].scale.x);
		shape.setPosition(reg.transforms[e].position);
		shape.setFillColor(sf::Color::White);
		g.GetWindow().draw(shape);
	}
}
