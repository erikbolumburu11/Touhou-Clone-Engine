#include <cstddef>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <Menus/EntityEditor.hpp>

Game::Game(unsigned int _windowWidth, unsigned int _windowHeight) 
	: windowWidth(_windowWidth), windowHeight(_windowHeight), event(sf::Event()) {

	window.create(sf::VideoMode({ _windowWidth, _windowHeight }, (unsigned int)32), "Bullet Hell Engine");
	if (!renderTexture.create({ _windowWidth, _windowHeight })) {
		std::cout << "ERROR CREATING RENDER TEXTURE!\n";
	}
	renderTarget = &window;

	view = sf::View(sf::FloatRect(
		{ 0.0f - _windowWidth / 2, 0.0f - _windowHeight / 2}, 
		{(float)_windowWidth, (float)_windowHeight}
	));

	GetEditorHandler() = EditorHandler();

	ImGui::SFML::Init(window);
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	
	#if (EDIT_MODE)
	IsGamePaused() = true;
	#endif

	#if (!EDIT_MODE) 
	IsGamePaused() = false;
	#endif
}

Game::~Game()
{
}

void Game::Run()
{
	while (IsRunning()) {
		// Window Events
		while (GetWindow().pollEvent(GetEvent())) {
			ImGui::SFML::ProcessEvent(GetWindow(), GetEvent());

			if (GetEvent().type == sf::Event::Closed) {
				GetWindow().close();
				IsRunning() = false;
			}

			#if (!EDIT_MODE)
			if (GetEvent().type == sf::Event::Resized) {
				view.setSize({ (float)GetWindow().getSize().x, (float)GetWindow().getSize().y});
			}
			#endif
		}

		GetWindow().setView(view);

		deltaTime = deltaClock.restart();

		#if (EDIT_MODE)
		GetRenderTexture().clear();
		#endif
		GetWindow().clear();

		if(!gamePaused) Update();
		Render();

		GetWindow().display();
	}
}

void Game::Update()
{
	spriteSystem.Update(*this, registry);
	transformSystem.Update(*this, registry);
	playerMovementSystem.Update(registry);
	bulletEmitterSystem.Update(*this);
	bulletSystem.Update(*this);
}

void Game::Render()
{
	#if (EDIT_MODE) 
	renderTarget = &renderTexture;
	#endif

	#if (!EDIT_MODE) 
	renderTarget = &window;
	#endif

	spriteSystem.Render(*this, registry);

	#if (EDIT_MODE)
	ImGui::SFML::Update(window, GetDeltaTime());
	GetEditorHandler().Update(*this);
	ImGui::SFML::Render(window);
	#endif
}
