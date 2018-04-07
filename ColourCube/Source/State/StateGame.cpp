#include "StateGame.h"
#include "GL/glew.h"
#include "StateMenu.h"

#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

#include "../UI/UIMaster.h"
#include "../UI/UIText.h"

#include "../Entity.h"
#include "../Level.h"

#include <iostream>

namespace State
{
	StateGame::StateGame()
		: m_Camera(nullptr), m_Renderer(nullptr), m_UI(nullptr), m_Level(nullptr)
	{

	}

	StateGame::~StateGame()
	{
		delete m_Level;
	}

	void StateGame::Init(GLFWwindow* window)
	{
		m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(window));
		m_Renderer = std::make_unique<Renderer::RendererMaster>(window, m_Camera);
		m_UI = std::make_unique<UI::UIMaster>();

		m_Level = new Level(std::make_unique<Input::InputGrid>(window, std::make_unique<Input::MousePicker>(m_Camera, window)));
		m_Camera->Target(m_Level);

		//m_Entities.emplace_back(m_Camera);
		m_Entities.emplace_back(m_Level);
		m_UI->AddText("Arial", std::make_unique<UI::UIText>("Text that expands onto multiple lines!",	4.0f, 0.01f, 0.0f, 100.0f, false));
		m_UI->AddText("Arial", std::make_unique<UI::UIText>("Test Smaller Text",						2.0f, 0.0f, 70.0f));

		m_UI->UpdateText();
	}

	void StateGame::Pause()
	{
		//std::cout << "Pause Game" << std::endl;
	}

	void StateGame::Resume()
	{
		//std::cout << "Resume Game" << std::endl;
	}

	void StateGame::HandleEvents(GameEngine* game)
	{
		for (const auto& entity : m_Entities)
			entity->HandleEvents();
		
		m_Camera->HandleEvents();
		
		if (glfwGetKey(game->GetWindow(), GLFW_KEY_T) == GLFW_PRESS)
			game->PushState(std::make_unique<StateMenu>());

		if (glfwGetKey(game->GetWindow(), GLFW_KEY_Y) == GLFW_PRESS)
			game->PopState();
		
		if (glfwGetKey(game->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(game->GetWindow()))
			game->Quit();
	}

	void StateGame::Update(GameEngine* game)
	{
		m_Camera->Update();

		for (const auto& entity : m_Entities)
			entity->Update();
	}

	void StateGame::Render()
	{
		m_Renderer->Clear();

		m_Renderer->PrepareEntity();
		for (auto* entity : m_Entities)
			m_Renderer->Render(entity);
		m_Renderer->EndRenderingEntity();

		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}

}