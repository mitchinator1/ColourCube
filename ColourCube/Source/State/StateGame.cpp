 #include "StateGame.h"

#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

#include "../UI/UIMaster.h"
#include "../UI/Element/UIText.h"

#include "../Level/Level.h"

namespace State
{
	StateGame::StateGame(std::shared_ptr<Display>& display)
		: StateBase(display), m_UI(std::make_unique<UI::UIMaster>(display))
		, m_Camera(std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(display), display))
		, m_Renderer(std::make_unique<Renderer::RendererMaster>(display->Window, m_Camera))
		, m_Level(std::make_unique<Level>("TestFile", std::make_unique<Input::InputGrid>(display), std::make_unique<Input::MousePicker>(m_Camera, display)))
	{
		m_Camera->Target(m_Level->GetPosition());
		m_UI->Build("Game");
		m_UI->Update();
	}

	StateGame::~StateGame()
	{

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
			m_UI->AddText("Arial", "win")
				->SetPosition(0.0f, 50.0f)
				->SetTime(0.75f)
				->SetSize(2.8f)
				->SetColour(0.6f, 0.7f, 0.9f)
				->SetCenter(true);
		}

		switch (m_UI->GetAction())
		{
		//TODO: Remove
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