#include "StateGame.h"
#include "GLFW/glfw3.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

namespace State
{
	StateGame::StateGame()
		: m_Level(nullptr), m_Camera(nullptr)
	{

	}

	StateGame::~StateGame()
	{
		delete m_Level;
		delete m_Camera;
	}

	void StateGame::Init(GLFWwindow* window)
	{
		m_Camera = new Camera::CameraBase(new Input::InputCamera(window));
		m_Level = new Level(new Input::InputGrid(window, new Input::MousePicker(m_Camera, window)));
		m_Camera->Target(m_Level);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		m_Entities.push_back(m_Camera);
		m_Entities.push_back(m_Level);

		m_Shader.Bind();
		m_Shader.SetUniformMat4("u_Projection", m_Camera->GetProjectionMatrix());
		m_Shader.SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader.SetUniformMat4("u_Model", m_Level->GetModelMatrix());
		m_Shader.SetUniform3f("u_LightColour", 1.0f, 1.0f, 1.0f);
		m_Shader.SetUniform3f("u_LightPos", m_Level->GetPosition().x, m_Level->GetPosition().y + 10.0f, m_Level->GetPosition().z + 5);
		m_Shader.SetUniform3f("u_ViewPos", m_Camera->GetPosition());
	}

	void StateGame::Pause()
	{

	}

	void StateGame::Resume()
	{

	}

	void StateGame::HandleEvents(GameEngine* game)
	{
		if (glfwGetKey(game->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(game->GetWindow()))
			game->Quit();

		for (const auto& entity : m_Entities)
			entity->HandleEvents();
	}

	void StateGame::Update(GameEngine* game)
	{
		for (const auto& entity : m_Entities)
			entity->Update();
	}

	void StateGame::Draw(GameEngine* game)
	{
		m_Renderer.Clear();
		m_Shader.Bind();
		m_Shader.SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader.SetUniform3f("u_ViewPos", m_Camera->GetPosition());
		for (const auto* e : m_Entities)
			m_Renderer.Draw(e);
		m_Shader.Unbind();
	}

}