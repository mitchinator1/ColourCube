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
	Grid* m_Grid;
	BasicCamera* m_Camera;
	Renderer m_Renderer;
	Shader m_Shader;
	std::vector<Entity*> m_Entities;

public:
	GameState();
	~GameState();

	void Init(GLFWwindow* window);

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);
};