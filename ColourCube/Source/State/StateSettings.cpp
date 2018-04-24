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

	}

	StateSettings::~StateSettings()
	{

	}

	void StateSettings::Init(std::shared_ptr<Display> display)
	{
		m_Display = display;
		m_Renderer = std::make_unique<Renderer::RendererMaster>(display->Window, std::make_shared<Camera::CameraBase>(nullptr, display));

		m_UI->AddText("Arial", "title", 3, 4.0f, 0.0f, 5.0f, { 1.0f, 1.0f, 1.0f });
		m_UI->AddButton("Arial", "menu", 0, ACTION::MENU, 0.0f, 0.0f, 20.0f, 10.0f, { 0.4f, 0.5f, 0.7f });

		m_UI->AddTextBox("Arial", "help", 3);
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

	void StateSettings::Render()
	{
		m_Renderer->Clear();

		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}
}
