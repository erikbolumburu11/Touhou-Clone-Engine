#include <cstddef>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <Menus/EntityEditor.hpp>

Game::Game(std::size_t _windowWidth, std::size_t _windowHeight) 
	: windowWidth(_windowWidth), windowHeight(_windowHeight), event(sf::Event()) {

	window.create(sf::VideoMode(_windowWidth, _windowHeight), "Bullet Hell Engine");
	if (!renderTexture.create(_windowWidth, _windowHeight)) {
		std::cout << "ERROR CREATING RENDER TEXTURE!\n";
	}
	renderTarget = &window;

	view = sf::View(sf::FloatRect(
		{ 0.0f - _windowWidth / 2, 0.0f - _windowHeight / 2}, 
		{(float)_windowWidth, (float)_windowHeight}
	));

	editorHandler = EditorHandler();
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

	for (Entity entity = 1; entity <= GetEntityCount(); entity++) {
		spriteSystem.Update(entity, *this, registry);
		transformSystem.Update(entity, deltaTime.asSeconds(), registry);
		playerMovementSystem.Update(entity, registry);
	}
}

void Game::Render()
{
	#if (EDIT_MODE) 
	renderTarget = &renderTexture;
	#endif

	#if (!EDIT_MODE) 
	renderTarget = &window;
	#endif

	for (Entity entity = 1; entity <= GetEntityCount(); entity++) {
		spriteSystem.Render(entity, *this, registry);
	}

	#if (EDIT_MODE)
	ImGui::SFML::Update(window, GetDeltaTime());
	GetEditorHandler().Update(GetDeltaTime().asSeconds(), *this);
	ImGui::SFML::Render(window);
	#endif
}

Entity Game::CreateEntity()
{
	static Entity entities = 0;
	++entities;
	GetEntityCount() = entities;
	return entities;
}
