#include <imgui.h>
#include "Menus/EditorBase.hpp"
#include <Game.hpp>

class ViewportEditor : public EditorBase {
public:
	virtual void Update(float delta, Game& game) override {
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		if (ImGui::Begin("Viewport")){
			ImVec2 contentSize = ImGui::GetContentRegionAvail();

			ImGui::Image(game.GetRenderTexture(), contentSize);
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

	virtual const char* GetName() override { return "Viewport"; }
};