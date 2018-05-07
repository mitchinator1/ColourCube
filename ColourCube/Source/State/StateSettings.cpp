#include "StateSettings.h"
#include "../Display.h"
#include "../UI/UIMaster.h"

#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"
#include "../Input/InputBase.h"

namespace State
{
	StateSettings::StateSettings()
		: m_UI(std::make_unique<UI::UIMaster>()), m_Renderer(nullptr), m_Display(nullptr)
	{
		m_UI->Build("Settings");
	}

	StateSettings::~StateSettings()
	{

	}

	void StateSettings::Init(std::shared_ptr<Display> display)
	{
		m_Display = display;
		m_Renderer = std::make_unique<Renderer::RendererMaster>(display->Window, std::make_shared<Camera::CameraBase>(nullptr, display));

		m_UI->AddTextBox("Arial", "settingshelp");
		m_UI->Update();
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

	void StateSettings::Render()
	{
		m_Renderer->Clear();

		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}
}
