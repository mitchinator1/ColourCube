#pragma once
#include "BasicState.h"
#include "../Renderer.h"
#include "../Grid.h"
#include "../Shader.h"
#include "../BasicCamera.h"
#include "../Entity.h"

class GameState : public BasicState
{
private:
	GameState();
	Renderer m_Renderer;
	Grid m_Grid;
	Shader m_Shader;
	BasicCamera m_Camera;
	std::vector<Entity*> m_Entities;

public:
	static GameState* GetInstance();

	void Init(GLFWwindow* window);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);
};