#include "StateGame.h"
#include "GLFW/glfw3.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

namespace State
{
	Game::Game()
		: m_Grid(nullptr), m_Camera(nullptr)
	{

	}

	Game::~Game()
	{
		delete m_Grid;
		delete m_Camera;
	}

	void Game::Init(GLFWwindow* window)
	{
		m_Camera = new Camera::CameraBase(new Input::Camera(window));
		m_Grid = new Grid(new Input::Grid(window, new Input::MousePicker(m_Camera, window)));
		m_Camera->Target(m_Grid);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		m_Entities.push_back(m_Camera);
		m_Entities.push_back(m_Grid);

		m_Shader.Bind();
		m_Shader.SetUniformMat4("u_Projection", m_Camera->GetProjectionMatrix());
		m_Shader.SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader.SetUniformMat4("u_Model", m_Grid->GetModelMatrix());
		m_Shader.SetUniform3f("u_LightColour", 1.0f, 1.0f, 1.0f);
		m_Shader.SetUniform3f("u_LightPos", m_Grid->GetPosition().x, m_Grid->GetPosition().y + 10.0f, m_Grid->GetPosition().z + 5);
		m_Shader.SetUniform3f("u_ViewPos", m_Camera->GetPosition());
	}

	void Game::Pause()
	{

	}

	void Game::Resume()
	{

	}

	void Game::HandleEvents(GameEngine* game)
	{
		if (glfwGetKey(game->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(game->GetWindow()))
			game->Quit();

		for (const auto& entity : m_Entities)
			entity->HandleEvents();
	}

	void Game::Update(GameEngine* game)
	{
		for (const auto& entity : m_Entities)
			entity->Update();
	}

	void Game::Draw(GameEngine* game)
	{
		m_Renderer.Clear();
		m_Shader.Bind();
		m_Shader.SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader.SetUniform3f("u_ViewPos", m_Camera->GetPosition());
		m_Renderer.Draw(*m_Grid);
		m_Shader.Unbind();
	}

}