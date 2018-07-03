#include "StateSettings.h"
#include "../UI/UIMaster.h"

#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"
#include "../Input/InputBase.h"

namespace State
{
	StateSettings::StateSettings(std::shared_ptr<Display>& display)
		: StateBase(display), m_UI(std::make_unique<UI::UIMaster>(display))
		, m_Renderer(std::make_unique<Renderer::RendererMaster>(display->Window, std::make_shared<Camera::CameraBase>(nullptr, display)))
	{
		m_UI->Build("Settings");
	}

	StateSettings::~StateSettings()
	{

	}

	void StateSettings::Pause()
	{

	}

	void StateSettings::Resume()
	{

	}

	void StateSettings::HandleEvents(GameEngine* game)
	{
		m_UI->HandleEvents(m_Display);

		if (glfwGetKey(m_Display->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Display->Window))
			game->Quit();
	}

	void StateSettings::Update(GameEngine* game)
	{
		switch (m_UI->GetAction())
		{
		case UI::ACTION::MENU:
			game->PopState();
			return;
		case UI::ACTION::EXIT:
			game->Quit();
			return;
		}

		m_UI->Update();
	}

	void StateSettings::Render() const
	{
		m_Renderer->Clear();

		m_Renderer->Render(m_UI.get());

		m_Renderer->Swap();
	}
}
