#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <Menus/EditorBase.hpp>
#include "Game.hpp"

class EntityEditor : public EditorBase {

	virtual void Update(Game& game) override {
		ImGui::Begin("Entity Editor");

		ImGui::Text("Entity Editor");

		ImGui::End();
	}

	const char* GetName() {
		return "Entity Editor";
	}
};