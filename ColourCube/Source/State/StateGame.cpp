 #include "StateGame.h"
#include <iostream>
#include "GL/glew.h"
#include "StateMenu.h"

#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

#include "../UI/UIMaster.h"
#include "../UI/UIText.h"

#include "../Entity.h"
#include "../Level.h"

#include "../Display.h"

namespace State
{
	StateGame::StateGame()
		: m_Camera(nullptr), m_Renderer(nullptr), m_UI(nullptr), m_Level(nullptr), m_Display(nullptr)
	{

	}

	StateGame::~StateGame()
	{
		delete m_Level;
	}

	void StateGame::Init(std::shared_ptr<Display> display)
	{
		m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(display->Window), display);
		m_Renderer = std::make_unique<Renderer::RendererMaster>(display->Window, m_Camera);
		m_UI = std::make_unique<UI::UIMaster>();
		m_Display = display;

		m_Level = new Level(std::make_unique<Input::InputGrid>(display->Window, std::make_unique<Input::MousePicker>(m_Camera, display)));
		m_Camera->Target(m_Level);

		//m_Entities.emplace_back(m_Camera);
		m_Entities.emplace_back(m_Level);
		//m_UI->AddText("Arial", "Text that expands onto multiple lines!", 4.0f, 0.01f, 0.0f, 100.0f, false));
		m_UI->AddText("Arial", "Test Smaller Text", 1.0f, 0.0f, 10.0f, { 0.4f, 0.3f, 0.7f });
		m_UI->AddButton("Arial", "Menu", 0.0f, 0.0f, 20.0f, 10.0f, { 0.4f, 0.5f, 0.7f });

		m_UI->UpdateText();
	}

	void StateGame::Pause()
	{
		//std::cout << "Pause Game" << std::endl;
	}

	void StateGame::Resume()
	{
		//std::cout << "Resume Game" << std::endl;
	}

	void StateGame::HandleEvents(GameEngine* game)
	{
		for (const auto& entity : m_Entities)
			entity->HandleEvents();
		
		m_UI->HandleEvents(m_Display);

		m_Camera->HandleEvents();
		
		if (glfwGetKey(m_Display->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Display->Window))
			game->Quit();

		if (glfwGetKey(m_Display->Window, GLFW_KEY_T) == GLFW_PRESS)
			game->PushState(std::make_unique<StateMenu>());
		
		if (glfwGetKey(m_Display->Window, GLFW_KEY_Y) == GLFW_PRESS)
			game->PopState();
	}

	void StateGame::Update(GameEngine* game)
	{
		m_Camera->Update();

		if (m_UI->GetAction() == 1)
			game->PopState();

		for (const auto& entity : m_Entities)
			entity->Update();
	}

	void StateGame::Render()
	{
		m_Renderer->Clear();

		m_Renderer->PrepareEntity();
		for (auto* entity : m_Entities)
			m_Renderer->Render(entity);
		m_Renderer->EndRenderingEntity();

		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}

}