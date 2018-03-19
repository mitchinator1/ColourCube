#include "StateGame.h"
#include "GLFW/glfw3.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

namespace State
{
	StateGame::StateGame()
		: m_Level(nullptr), m_Camera(nullptr), m_Renderer(nullptr)
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

		m_Renderer = new Renderer::RendererBase(m_Camera);

		m_Entities.push_back(m_Camera);
		m_Entities.push_back(m_Level);
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
		m_Renderer->Clear();

		for (auto* e : m_Entities)
			m_Renderer->Render(e);
	}

}