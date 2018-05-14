 #include "StateGame.h"
#include <iostream>
#include "../Display.h"

#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

#include "../UI/UIMaster.h"
#include "../UI/UIText.h"

#include "../Level/Level.h"

namespace State
{
	StateGame::StateGame()
		: m_Camera(nullptr), m_Renderer(nullptr), m_UI(std::make_unique<UI::UIMaster>()), m_Level(nullptr), m_Display(nullptr)
	{
		m_UI->Build("Game");
	}

	StateGame::~StateGame()
	{

	}

	void StateGame::Init(std::shared_ptr<Display> display)
	{
		m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(display->Window), display);
		m_Renderer = std::make_unique<Renderer::RendererMaster>(display->Window, m_Camera);
		m_Display = display;

		m_Level = std::make_unique<Level>("TestFile", std::make_unique<Input::InputGrid>(display->Window), std::make_unique<Input::MousePicker>(m_Camera, display));
		m_Camera->Target(m_Level->GetPosition());

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
		m_Camera->HandleEvents();
		m_UI->HandleEvents(m_Display);
		
		if (glfwGetKey(m_Display->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Display->Window))
			game->Quit();
	}

	void StateGame::Update(GameEngine* game)
	{
		m_Camera->Update();
		m_Level->Update();

		if (m_Level->CheckWin())
		{
			m_UI->AddText("Arial", "win", 0.0f, 50.0f)
				->SetTime(0.8f)
				->SetSize(2.8f)
				->SetColour(0.5f, 0.5f, 0.8f);
		}

		switch (m_UI->GetAction())
		{
		case UI::ACTION::CONTINUE:
			m_UI->Continue();
			break;
		case UI::ACTION::MENU:
			game->PopState();
			return;
		case UI::ACTION::EXIT:
			game->Quit();
			return;
		}

		m_UI->Update();
	}

	void StateGame::Render() const
	{
		m_Renderer->Clear();

		m_Renderer->Render(*m_Level);
		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}

}