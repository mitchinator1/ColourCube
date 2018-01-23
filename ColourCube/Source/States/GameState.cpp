#include "GameState.h"
#include "GLFW/glfw3.h"

#include "../CameraInput.h"
#include "../BasicCamera.h"

GameState* GameState::GetInstance()
{
	static GameState instance;
	return &instance;
}

void GameState::Init()
{
	glEnable(GL_CULL_FACE);

	m_Shader.Bind();

	CameraInput camInput;
	BasicCamera camera(&camInput);
	//camera.Bind(window);

	m_Shader.SetUniformMat4("u_Projection", camera.GetProjectionMatrix(1400, 900));
	m_Shader.SetUniformMat4("u_View", camera.GetViewMatrix());
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

void GameState::HandleEvents()
{

}

void GameState::Update()
{

}

void GameState::Draw()
{
	m_Renderer.Clear();
	m_Renderer.Draw(m_Grid);
}
