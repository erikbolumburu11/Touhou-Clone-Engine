#pragma once
#include <Menus/EditorBase.hpp>
#include <vector>

class Game;

class EditorHandler {
public:
	EditorHandler();
	void Update(float delta, Game& game);

	void MainMenuBar(Game& game);
	void OpenHandler();
	void CloseHandler();

	std::vector<EditorBase*> editors;
	uint32_t mainDockID = 0;
};