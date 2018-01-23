#pragma once
#include "BasicState.h"
#include "../Renderer.h"
#include "../Grid.h"
#include "../Shader.h"

class GameState : public BasicState
{
private:
	GameState() {}
	Renderer m_Renderer;
	Grid m_Grid;
	Shader m_Shader;
public:
	static GameState* GetInstance();

	void Init();
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();
};