 #include "StateGame.h"
#include "../Input/MousePicker.h"
#include "../Input/InputCamera.h"

#include "../Level/Level.h"

namespace State
{
	StateGame::StateGame(std::shared_ptr<Display>& display)
		: StateBase(display)
		, m_Level(std::make_unique<Level>(0, std::make_unique<Input::MousePicker>(m_Camera, display)))
	{
		m_Camera->AddInput(std::make_unique<Input::InputCamera>(display));
		m_Camera->Target(m_Level->GetPosition());
		m_UI->Build("Game");
	}

	StateGame::~StateGame()
	{

	}

	void StateGame::HandleEvents(GameEngine* game)
	{
		if (!m_UI->HandleEvents(m_Display))
			m_Level->HandleEvents();
		m_Camera->HandleEvents();
		
		if (glfwGetKey(m_Display->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Display->Window))
			game->Quit();
	}

	void StateGame::Update(GameEngine* game)
	{
		m_Camera->Update();
		m_Level->Update();

		if (m_Level->CubesMatch())
		{
			m_UI->Reveal("Win");
		}

		switch (m_UI->GetAction())
		{
		case UI::ACTION::LOAD: {
			m_Level = std::make_unique<Level>(m_UI->GetLevelNumber(), m_Level.get());
			m_Camera->Target(m_Level->GetPosition());
		}
			break;
		case UI::ACTION::MENU: {
			game->PopState();
		}
			return;
		case UI::ACTION::EXIT: {
			game->Quit();
		}
			return;
		}

		m_UI->Update();
	}

	void StateGame::Render() const
	{
		m_Renderer->Clear();

		m_Renderer->Render(m_Level->GetMesh());
		m_Renderer->Render(m_UI.get());

		m_Renderer->Swap();
	}

}