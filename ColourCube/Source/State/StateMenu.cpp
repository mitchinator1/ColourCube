#include "StateMenu.h"
#include "StateGame.h"
#include "StateEditor.h"
#include "StateSettings.h"
#include "../Input/InputCamera.h"
#include "../Camera/CameraBase.h"
#include "../Renderer/RendererMaster.h"
#include "../UI/UIMaster.h"
#include "../Display.h"

namespace State
{
	StateMenu::StateMenu() noexcept
		: m_UI(std::make_unique<UI::UIMaster>()), m_Renderer(nullptr), m_Display(nullptr)
	{
		m_UI->Build("Menu");
	}

	StateMenu::~StateMenu()
	{

	}

	void StateMenu::Init(std::shared_ptr<Display>& display)
	{
		m_Renderer = std::make_unique<Renderer::RendererMaster>(display->Window, std::make_shared<Camera::CameraBase>(nullptr, display));
		m_Display = display;
	}

	void StateMenu::Pause()
	{

	}

	void StateMenu::Resume()
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
		//TODO: Remove Continue function
		case UI::ACTION::CONTINUE:
			m_UI->Continue();
			break;
		case UI::ACTION::PLAY:
			game->PushState(std::make_unique<StateGame>());
			return;
		case UI::ACTION::EDITOR:
			game->PushState(std::make_unique<StateEditor>());
			return;
		case UI::ACTION::SETTINGS:
			game->PushState(std::make_unique<StateSettings>());
			return;
		case UI::ACTION::EXIT:
			game->Quit();
			return;
		}

		m_UI->Update();
	}

	void StateMenu::Render() const
	{
		m_Renderer->Clear();

		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}
}