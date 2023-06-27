#pragma once 

#define EDIT_MODE true

#include <cstddef>
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include "Systems/SpriteSystem.hpp"
#include "Systems/TransformSystem.hpp"
#include "Systems/PlayerMovementSystem.hpp"
#include "Systems/BulletEmitterSystem.hpp"
#include "Systems/BulletSystem.hpp"
#include "Menus/EditorHandler.hpp"
#include "BulletHandler.hpp"

class Game {
public:
	Game(unsigned int _windowWidth, unsigned int _windowHeight);
	~Game();

	void Run();
	void Update();
	void Render();

	sf::RenderWindow& GetWindow()			{ return window;					}
	sf::RenderTexture& GetRenderTexture()	{ return renderTexture;				}
	sf::RenderTarget* GetRenderTarget()		{ return renderTarget;				}
	sf::View& GetView()						{ return view;						}
	sf::Event& GetEvent()					{ return event;						}
	bool& IsRunning()						{ return isRunning;					}
	bool& IsGamePaused()					{ return gamePaused;				}
	entt::registry& GetRegistry()			{ return registry;					}
	sf::Time& GetDeltaTime()				{ return deltaTime;					}
	EditorHandler& GetEditorHandler()		{ return editorHandler;				}
	BulletHandler& GetBulletHandler()		{ return bulletHandler;				}

private:
	std::size_t windowWidth;
	std::size_t windowHeight;

	sf::RenderTarget* renderTarget;
	sf::RenderTexture renderTexture;
	sf::RenderWindow window;

	sf::View view;

	sf::Clock deltaClock;
	sf::Time deltaTime;

	EditorHandler editorHandler;

	BulletHandler bulletHandler;

	bool isRunning = true;
	bool gamePaused = false;
	sf::Event event;

	entt::registry registry;

	SpriteSystem spriteSystem;
	TransformSystem transformSystem;
	PlayerMovementSystem playerMovementSystem;
	BulletEmitterSystem bulletEmitterSystem;
	BulletSystem bulletSystem;
};