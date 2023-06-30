#include "Systems/SpriteSystem.hpp"
#include "Game.hpp"

void SpriteSystem::Update(Game& g, entt::registry& reg) {
}

void SpriteSystem::Render(Game& g, entt::registry& reg)
{
	////////////////////////////
	/////// Draw Bullets ///////
	////////////////////////////

	// Create maps of of BulletData and sf::VertexArray.
	// After creating each quad, push it to the vertex array map 
	// Render each map in order of their bullet data draw layer index

	int size = 0;
	auto bulletView = reg.view<SpriteComponent, TransformComponent, BulletComponent>();
	bulletView.each([&](SpriteComponent& sr, TransformComponent& tc, BulletComponent& bc) {
		size++;
	});

	sf::VertexArray va(sf::PrimitiveType::Triangles, size * 6);
	bulletView.each([&](SpriteComponent& sr, TransformComponent& tc, BulletComponent& bc) {
		sf::VertexArray quad = sf::VertexArray();
		quad.setPrimitiveType(sf::PrimitiveType::Triangles);
		quad.resize(6);

		quad[0].position = sf::Vector2f(tc.position.x, tc.position.y);
		quad[1].position = sf::Vector2f(tc.position.x + tc.scale.x, tc.position.y);
		quad[2].position = sf::Vector2f(tc.position.x, tc.position.y + tc.scale.y);
		quad[3].position = sf::Vector2f(tc.position.x, tc.position.y + tc.scale.y);
		quad[4].position = sf::Vector2f(tc.position.x + tc.scale.x, tc.position.y);
		quad[5].position = sf::Vector2f(tc.position.x + tc.scale.x, tc.position.y + tc.scale.y);

		//Rotate
		sf::Vector2f center = quad[0].position + (tc.scale / 2.f);
		for (uint8_t i = 0; i < 6; i++)
		{
			sf::Vector2f diffVec = quad[i].position - center;
			sf::Vector2f newVertPos = diffVec.rotatedBy(sf::radians(atan2(bc.angle.y, bc.angle.x)));
			quad[i].position = newVertPos + center;
		}

		for (uint8_t i = 0; i < 6; i++)
		{
			quad[i].color = sr.color;
		}

		uint16_t texStartPos = bc.bullet.states[bc.bullet.currentState].textureIndex * BULLET_SPRITE_SCALE_PX;

		quad[0].texCoords = sf::Vector2f(texStartPos, 0);
		quad[1].texCoords = sf::Vector2f(texStartPos + BULLET_SPRITE_SCALE_PX, 0);
		quad[2].texCoords = sf::Vector2f(texStartPos, BULLET_SPRITE_SCALE_PX);
		quad[3].texCoords = sf::Vector2f(texStartPos, BULLET_SPRITE_SCALE_PX);
		quad[4].texCoords = sf::Vector2f(texStartPos + BULLET_SPRITE_SCALE_PX, 0);
		quad[5].texCoords = sf::Vector2f(texStartPos + BULLET_SPRITE_SCALE_PX, BULLET_SPRITE_SCALE_PX);

		for (int i = 0; i < 6; i++)
		{
			va.append(quad[i]);
		}
	});
	g.GetRenderTarget()->draw(va, &g.GetResourceManager().GetBulletTextureMap()->getTexture());

	////////////////////////////
	/////// Draw Else //////////
	////////////////////////////
	auto view = reg.view<SpriteComponent, TransformComponent>(entt::exclude<BulletComponent>);
	view.each([&](SpriteComponent& sr, TransformComponent& tc) {
		sf::VertexArray quad = sf::VertexArray();
		quad.setPrimitiveType(sf::PrimitiveType::Triangles);
		quad.resize(6);

		quad[0].position = sf::Vector2f(tc.position.x, tc.position.y);
		quad[1].position = sf::Vector2f(tc.position.x + tc.scale.x, tc.position.y);
		quad[2].position = sf::Vector2f(tc.position.x, tc.position.y + tc.scale.y);
		quad[3].position = sf::Vector2f(tc.position.x, tc.position.y + tc.scale.y);
		quad[4].position = sf::Vector2f(tc.position.x + tc.scale.x, tc.position.y);
		quad[5].position = sf::Vector2f(tc.position.x + tc.scale.x, tc.position.y + tc.scale.y);

		//Offset by half the transform
		for (uint8_t i = 0; i < 6; i++) {
			quad[i].position -= tc.scale / 2.f;
		}

		quad[0].texCoords = sf::Vector2f(0, 0);
		quad[1].texCoords = sf::Vector2f(0 + tc.scale.x, 0);
		quad[2].texCoords = sf::Vector2f(0, tc.scale.y);
		quad[3].texCoords = sf::Vector2f(0, tc.scale.y);
		quad[4].texCoords = sf::Vector2f(0 + tc.scale.x, 0);
		quad[5].texCoords = sf::Vector2f(0 + tc.scale.x, tc.scale.y);

		g.GetRenderTarget()->draw(quad, &sr.texture);
	});
}
