#pragma once

class Game;

class EditorBase {
public:
	EditorBase() = default;

	virtual const char* GetName() = 0;
	virtual void Update(float dt, Game& game) {};
};