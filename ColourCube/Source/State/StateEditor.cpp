#include "StateEditor.h"

#include "../Input/InputGrid.h"
#include "../Input/EditorMousePicker.h"
#include "../Input/InputCamera.h"

#include "../Display.h"
#include "../Camera/CameraBase.h"
#include "../Renderer/RendererMaster.h"
#include "../Renderer/RendererGrid.h"
#include "../UI/UIMaster.h"

#include "../Level/Level.h"
#include "../Level/Gridline.h"
#include "../Level/LevelSaver.h"

namespace State
{
	StateEditor::StateEditor()
		: m_UI(std::make_unique<UI::UIMaster>()), m_Camera(nullptr), m_Level(nullptr), m_Renderer(nullptr)
		, m_Grid(std::make_unique<Gridline>(5, 5)), m_RendererGrid(nullptr)
	{

	}

	StateEditor::~StateEditor()
	{

	}

	void StateEditor::Init(std::shared_ptr<Display> display)
	{
		m_Display = display;
		m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(display->Window), display);
		m_Renderer = std::make_unique<Renderer::RendererMaster>(display->Window, m_Camera);
		m_RendererGrid = std::make_unique<Renderer::RendererGrid>(m_Camera);

		m_Level = std::make_unique<Level>("BlankLevel", std::make_unique<Input::InputGrid>(display->Window), std::make_unique<Input::EditorMousePicker>(m_Camera, display));
		m_Camera->Target(m_Level->GetPosition());

		m_UI->AddText("Arial", "title", 2, 1.5f, 0.0f, 0.0f, { 0.4f, 0.3f, 0.7f });
		m_UI->AddButton("Arial", "menu", 0, ACTION::MENU, 0.0f, 0.0f, 20.0f, 9.0f, { 0.4f, 0.5f, 0.7f });
		m_UI->AddButton("Arial", "menu", 5, ACTION::LOAD, 0.0f, 9.0f, 20.0f, 9.0f, { 0.25f, 0.4f, 0.7f });
		m_UI->AddButton("Arial", "menu", 6, ACTION::SAVE, 0.0f, 18.0f, 20.0f, 9.0f, { 0.10f, 0.3f, 0.7f });
		m_UI->AddButton("Arial", "menu", 7, ACTION::TOGGLE, 0.0f, 27.0f, 20.0f, 9.0f, { 0.0f, 0.2f, 0.7f });

		m_UI->Update();
	}

	void StateEditor::Pause()
	{

	}

	void StateEditor::Resume()
	{

	}

	void StateEditor::HandleEvents(GameEngine* game)
	{
		m_Level->HandleEvents();
		m_Camera->HandleEvents();
		m_UI->HandleEvents(m_Display);

		if (glfwGetKey(m_Display->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Display->Window))
			game->Quit();
	}

	void StateEditor::Update(GameEngine* game)
	{
		switch (m_UI->GetAction())
		{
		case ACTION::CONTINUE: {
			m_UI->Continue();
		}
			break;
		case ACTION::MENU: {
			game->PopState();
		}
			return;
		case ACTION::LOAD: {
			std::cout << "Load Level Option" << '\n';
		}
			break;
		case ACTION::SAVE: {
			LevelSaver save(m_Level.get());
		}
			break;
		case ACTION::TOGGLE: {
			m_Level->ToggleMode();
			std::cout << "Input Toggled" << '\n';
		}
			break;
		case ACTION::EXIT: {
			game->Quit();
		}
			return;
		}

		m_Camera->Update();
		m_Level->Update();
		m_UI->Update();
	}

	void StateEditor::Render()
	{
		m_Renderer->Clear();

		m_RendererGrid->Render(*m_Grid);
		m_Renderer->Render(*m_Level);
		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}
}