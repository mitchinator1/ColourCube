#include "GameState.h"
#include "GLFW/glfw3.h"

#include "../Input/CameraInput.h"

GameState* GameState::GetInstance()
{
	static GameState instance;
	return &instance;
}

GameState::GameState()
	: m_Camera()
{

}

void GameState::Init(GLFWwindow* window)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	m_Shader.Bind();

	CameraInput* camInput = new CameraInput();
	m_Camera.AddInput(camInput);
	m_Camera.Bind(window);
	m_Camera.Focus(&m_Grid);

	m_Entities.push_back(&m_Camera);
	m_Entities.push_back(&m_Grid);
	
	m_Shader.SetUniformMat4("u_Projection", m_Camera.GetProjectionMatrix(1800, 1200));
	m_Shader.SetUniformMat4("u_View", m_Camera.GetViewMatrix());
	m_Shader.SetUniformMat4("u_Model", m_Grid.GetModelMatrix());
}

void GameState::CleanUp()
{
	
}

void GameState::Pause()
{

}

void GameState::Resume()
{

}

void GameState::HandleEvents(GameEngine* game)
{
	if (glfwGetKey(game->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(game->GetWindow()))
		game->Quit();

	for (unsigned int i = 0; i < m_Entities.size(); i++)
		m_Entities[i]->HandleEvents();
}

void GameState::Update(GameEngine* game)
{
	for (unsigned int i = 0; i < m_Entities.size(); i++)
		m_Entities[i]->Update();
}

void GameState::Draw(GameEngine* game)
{
	m_Renderer.Clear();
	m_Shader.Bind();
	m_Shader.SetUniformMat4("u_View", m_Camera.GetViewMatrix());
	m_Renderer.Draw(m_Grid);
	m_Shader.Unbind();
}
