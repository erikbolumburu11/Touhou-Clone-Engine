#include "Menus/EditorHandler.hpp"
#include "Menus/EntityEditor.hpp"
#include "Menus/ViewportEditor.hpp"
#include <Game.hpp>

EditorHandler::EditorHandler()
{
	editors.push_back(new EntityEditor());
	editors.push_back(new ViewportEditor());
}

void EditorHandler::Update(float delta, Game& game)
{
	MainMenuBar(game);
	OpenHandler();

	for (EditorBase* e : editors) {
		e->Update(delta, game);
	}

	CloseHandler();
}


void EditorHandler::OpenHandler()
{
	ImGuiWindowFlags windowFlags {
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoNavFocus 
	};

	ImGuiDockNodeFlags dockFlags{
		ImGuiDockNodeFlags_None
	};

	const ImGuiViewport* imGuiViewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(imGuiViewport->WorkPos);
	ImGui::SetNextWindowSize(imGuiViewport->WorkSize);
	ImGui::SetNextWindowViewport(imGuiViewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("SFML Window", nullptr, windowFlags);
	ImGui::PopStyleVar(3);
	mainDockID = ImGui::GetID("Main"); // IF PROBLEM CHECK HERE. WHAT IS MAIN?
	ImGui::DockSpace(mainDockID, ImVec2(0.0f, 0.0f), dockFlags);
}

void EditorHandler::CloseHandler()
{
	ImGui::End();
}

void EditorHandler::MainMenuBar(Game& game)
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {

			ImGui::Button("New");
			ImGui::Button("Close");

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			ImGui::Button("Undo");
			ImGui::Button("Redo");

			ImGui::EndMenu();
		}

		if (game.IsGamePaused()) {
			if (ImGui::Button("Game Paused")) {
				game.IsGamePaused() = !game.IsGamePaused();
			}
		}
		if (!game.IsGamePaused()) {
			if (ImGui::Button("Game Running")) {
				game.IsGamePaused() = !game.IsGamePaused();
			}
		}


		ImGui::EndMainMenuBar();
	}
}
