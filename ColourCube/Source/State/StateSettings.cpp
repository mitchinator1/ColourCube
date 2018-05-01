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
		m_UI->AddText("Arial", "title", 3, 3.0f, 0.0f, 0.0f, { 1.0f, 1.0f, 1.0f });
		m_UI->AddButton("Arial", "menu", 0, ACTION::MENU, 0.0f, 0.0f, 20.0f, 10.0f, { 0.4f, 0.5f, 0.7f });

		m_UI->AddBackground(UI::TYPE::BACKGROUND, 0.0f, 0.0f, 100.0f, 100.0f, { 0.5f, 0.7f, 0.5f });

		m_UI->AddText("Arial", "slider", 0, 1.2f, -44.0f, 19.0f, { 1.0f, 0.4f, 0.4f });
		m_UI->AddSlider(10.0f, 18.0f, 30.0f);
		m_UI->AddText("Arial", "slider", 1, 1.2f, -44.0f, 27.0f, { 0.4f, 1.0f, 0.4f });
		m_UI->AddSlider(10.0f, 26.0f, 30.0f);
		m_UI->AddText("Arial", "slider", 2, 1.2f, -44.0f, 35.0f, { 0.4f, 0.4f, 1.0f });
		m_UI->AddSlider(10.0f, 34.0f, 30.0f);
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
