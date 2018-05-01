#include "StateMenu.h"
#include <iostream>
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
	StateMenu::StateMenu()
		: m_UI(std::make_unique<UI::UIMaster>()), m_Renderer(nullptr), m_Display(nullptr)
	{
		m_UI->AddBackground(UI::TYPE::BACKGROUND, 0.0f, 0.0f, 100.0f, 100.0f, { 0.2f, 0.2f, 0.4f });

		m_UI->AddText("Arial", "title", 0, 4.0f, 0.0f, 5.0f, { 1.0f, 1.0f, 1.0f });
		m_UI->AddButton("Arial", "menu", 1, ACTION::PLAY, 40.0f, 50.0f, 20.0f, 10.0f, { 1.0f, 0.6f, 1.0f });
		m_UI->AddButton("Arial", "menu", 2, ACTION::EDITOR, 40.0f, 60.0f, 20.0f, 10.0f, { 0.8f, 0.7f, 0.9f });
		m_UI->AddButton("Arial", "menu", 3, ACTION::SETTINGS, 40.0f, 70.0f, 20.0f, 10.0f, { 0.5f, 0.8f, 0.6f });
		m_UI->AddButton("Arial", "menu", 4, ACTION::EXIT, 40.0f, 80.0f, 20.0f, 10.0f, { 0.3f, 0.7f, 0.9f });
	}

	StateMenu::~StateMenu()
	{

	}

	void StateMenu::Init(std::shared_ptr<Display> display)
	{
		m_Renderer = std::make_unique<Renderer::RendererMaster>(display->Window, std::make_shared<Camera::CameraBase>(nullptr, display));
		m_Display = display;

		//m_UI->AddTextBox("Arial", "menuhelp");
		m_UI->Update();
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
		case ACTION::CONTINUE:
			m_UI->Continue();
			break;
		case ACTION::PLAY:
			game->PushState(std::make_unique<StateGame>());
			return;
		case ACTION::EDITOR:
			game->PushState(std::make_unique<StateEditor>());
			return;
		case ACTION::SETTINGS:
			game->PushState(std::make_unique<StateSettings>());
			return;
		case ACTION::EXIT:
			game->Quit();
			return;
		}

		m_UI->Update();
	}

	void StateMenu::Render()
	{
		m_Renderer->Clear();

		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}
}