 #include "StateGame.h"
#include <iostream>
#include "../Display.h"

#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

#include "../UI/UIMaster.h"

#include "../Level/Level.h"

namespace State
{
	StateGame::StateGame()
		: m_Camera(nullptr), m_Renderer(nullptr), m_UI(std::make_unique<UI::UIMaster>()), m_Level(nullptr), m_Display(nullptr)
	{

	}

	StateGame::~StateGame()
	{

	}

	void StateGame::Init(std::shared_ptr<Display> display)
	{
		m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(display->Window), display);
		m_Renderer = std::make_unique<Renderer::RendererMaster>(display->Window, m_Camera);
		m_Display = display;

		m_Level = std::make_unique<Level>("TestFile", std::make_unique<Input::InputGrid>(display->Window),  std::make_unique<Input::MousePicker>(m_Camera, display));
		m_Camera->Target(m_Level->GetPosition());

		m_UI->AddText("Arial", "title", 1, 1.5f, 0.0f, 0.0f, { 0.4f, 0.3f, 0.7f });
		m_UI->AddButton("Arial", "menu", 0, ACTION::MENU, 0.0f, 0.0f, 20.0f, 10.0f, { 0.4f, 0.5f, 0.7f });
		m_UI->Update();
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
		m_Level->HandleEvents();
		
		m_UI->HandleEvents(m_Display);

		m_Camera->HandleEvents();
		
		if (glfwGetKey(m_Display->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Display->Window))
			game->Quit();
	}

	void StateGame::Update(GameEngine* game)
	{
		m_Camera->Update();
		m_Level->Update();

		if (m_Level->CheckWin())
		{
			m_UI->AddText("Arial", "win", 0, 3.0f, 0.0f, 40.0f, { 0.5f, 0.5f, 0.5f });
			m_UI->AddTextBox("Arial", "winhelp");
		}

		switch (m_UI->GetAction())
		{
		case ACTION::CONTINUE:
			m_UI->Continue();
			break;
		case ACTION::MENU:
			game->PopState();
			return;
		case ACTION::EXIT:
			game->Quit();
			return;
		}

		m_UI->Update();
	}

	void StateGame::Render()
	{
		m_Renderer->Clear();

		m_Renderer->Render(*m_Level);
		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}

}