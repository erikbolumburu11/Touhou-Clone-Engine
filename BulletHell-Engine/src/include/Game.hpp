#pragma once 

#define EDIT_MODE true

#include <cstddef>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include "Components/Registry.hpp"
#include "Systems/SpriteSystem.hpp"
#include "Systems/TransformSystem.hpp"
#include "Systems/PlayerMovementSystem.hpp"
#include "Menus/EditorHandler.hpp"

using Entity = std::size_t;

class Game {
public:
	Game(std::size_t _windowWidth, std::size_t _windowHeight);
	~Game();

	void Run();
	void Update();
	void Render();

	Entity CreateEntity();

	sf::RenderWindow& GetWindow()			{ return window;				}
	sf::RenderTexture& GetRenderTexture()	{ return renderTexture;			}
	sf::RenderTarget* GetRenderTarget()		{ return renderTarget;			}
	sf::Event& GetEvent()					{ return event;					}
	bool& IsRunning()						{ return isRunning;				}
	Entity& GetEntityCount()				{ return entityCount;			}
	Registry& GetRegistry()					{ return registry;				}
	sf::Time& GetDeltaTime()				{ return deltaTime;				}
	EditorHandler& GetEditorHandler()		{ return editorHandler;			}

private:
	std::size_t windowWidth;
	std::size_t windowHeight;

	sf::RenderTarget* renderTarget;
	sf::RenderTexture renderTexture;
	sf::RenderWindow window;

	sf::Clock deltaClock;
	sf::Time deltaTime;

	EditorHandler editorHandler;

	bool isRunning = true;
	sf::Event event;

	Entity entityCount = 0;

	Registry registry; // Stores entity, component maps.

	SpriteSystem spriteSystem;
	TransformSystem transformSystem;
	PlayerMovementSystem playerMovementSystem;
};