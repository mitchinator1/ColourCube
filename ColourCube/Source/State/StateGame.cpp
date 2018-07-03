 #include "StateGame.h"

#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

#include "../UI/UIMaster.h"

#include "../Level/Level.h"

namespace State
{
	StateGame::StateGame(std::shared_ptr<Display>& display)
		: StateBase(display), m_UI(std::make_unique<UI::UIMaster>(display))
		, m_Camera(std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(display), display))
		, m_Renderer(std::make_unique<Renderer::RendererMaster>(display->Window, m_Camera))
		, m_Level(std::make_unique<Level>("BlankLevel", std::make_unique<Input::InputGrid>(display), std::make_unique<Input::MousePicker>(m_Camera, display)))
	{
		m_Camera->Target(m_Level->GetPosition());
		m_UI->Build("Game");
	}

	StateGame::~StateGame()
	{

	}

	void StateGame::Pause()
	{

	}

	void StateGame::Resume()
	{

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
			m_UI->Reveal("Win");
		}

		switch (m_UI->GetAction())
		{
		case UI::ACTION::LOAD: {
			m_Level.reset();
			m_Level = std::make_unique<Level>(m_UI->GetID(),
				std::make_unique<Input::InputGrid>(game->GetDisplay()),
				std::make_unique<Input::MousePicker>(m_Camera, game->GetDisplay()));
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