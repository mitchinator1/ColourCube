#include "StateMenu.h"
#include "StateGame.h"
#include "StateEditor.h"
#include "StateSettings.h"

namespace State
{
	StateMenu::StateMenu(std::shared_ptr<Display>& display)
		: StateBase(display)
	{
		m_UI->Build("Menu");
	}

	StateMenu::~StateMenu()
	{

	}
	
	void StateMenu::HandleEvents(GameEngine* game)
	{
		m_UI->HandleEvents(m_Display);

		if (glfwGetKey(m_Display->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Display->Window))
			game->Quit();
	}

	void StateMenu::Update(GameEngine* game)
	{
		switch (m_UI->GetAction())
		{
		case UI::ACTION::ADD_COLOUR: {
			m_UI->GetColour();
			break;
		}
		case UI::ACTION::PLAY: {
			game->PushState(std::make_unique<StateGame>(m_Display));
			return;
		}
		case UI::ACTION::EDITOR: {
			game->PushState(std::make_unique<StateEditor>(m_Display));
			return;
		}
		case UI::ACTION::SETTINGS: {
			game->PushState(std::make_unique<StateSettings>(m_Display));
			return;
		}
		case UI::ACTION::EXIT: {
			game->Quit();
			return;
		}
		}

		m_UI->Update();
	}

	void StateMenu::Render() const
	{
		m_Renderer->Clear();

		m_Renderer->Render(m_UI.get());

		m_Renderer->Swap();
	}
}