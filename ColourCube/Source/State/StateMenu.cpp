#include "StateMenu.h"
#include <iostream>
#include "StateGame.h"
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

	}

	StateMenu::~StateMenu()
	{

	}

	void StateMenu::Init(std::shared_ptr<Display> display)
	{
		m_Renderer = std::make_unique<Renderer::RendererMaster>(display->Window,
			std::make_shared<Camera::CameraBase>(nullptr, display));
		m_Display = display;

		m_UI->AddText("Arial", "Colour Cube!", 4.0f, 0.0f, 5.0f, { 1.0f, 1.0f, 1.0f });
		m_UI->AddButton("Arial", "Play", 40.0f, 50.0f, 20.0f, 10.0f, { 1.0f, 0.6f, 1.0f });
		m_UI->AddButton("Arial", "Editor", 40.0f, 60.0f, 20.0f, 10.0f, { 0.8f, 0.7f, 0.9f });
		m_UI->AddButton("Arial", "Settings", 40.0f, 70.0f, 20.0f, 10.0f, { 0.5f, 0.8f, 0.6f });
		m_UI->AddButton("Arial", "Exit", 40.0f, 80.0f, 20.0f, 10.0f, { 0.3f, 0.7f, 0.9f });
		m_UI->AddBackground(0.0f, 0.0f, 100.0f, 100.0f, { 0.2f, 0.2f, 0.4f });
		m_UI->UpdateText();
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

		if (glfwGetKey(m_Display->Window, GLFW_KEY_T) == GLFW_PRESS)
			game->PushState(std::make_unique<StateGame>());

		if (glfwGetKey(m_Display->Window, GLFW_KEY_Y) == GLFW_PRESS)
			game->PopState();

	}

	void StateMenu::Update(GameEngine* game)
	{
		if (m_UI->GetAction() == 1)
			game->PushState(std::make_unique<StateGame>());

		if (m_UI->GetAction() == 4)
			game->Quit();
	}

	void StateMenu::Render()
	{
		m_Renderer->Clear();

		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}
}