#include "StateEditor.h"

#include "../Input/EditorMousePicker.h"
#include "../Input/InputCamera.h"

#include "../Camera/CameraBase.h"
#include "../Renderer/RendererMaster.h"
#include "../Renderer/RendererGrid.h"
#include "../UI/UIMaster.h"

#include "../Level/Level.h"
#include "../Level/Gridline.h"
#include "../Level/LevelSaver.h"

namespace State
{
	StateEditor::StateEditor(std::shared_ptr<Display>& display)
		: StateBase(display), m_UI(std::make_unique<UI::UIMaster>(display))
		, m_Camera(std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(display), display))
		, m_Renderer(std::make_unique<Renderer::RendererMaster>(display->Window, m_Camera))
		, m_RendererGrid(std::make_unique<Renderer::RendererGrid>(m_Camera))
		, m_Level(std::make_unique<Level>("BlankLevel", std::make_unique<Input::EditorMousePicker>(m_Camera, display)))
		, m_Grid(std::make_unique<Gridline>(5, 5))
	{
		m_Camera->Target(m_Level->GetPosition());
		m_UI->Build("Editor");
	}

	StateEditor::~StateEditor()
	{

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
		case UI::ACTION::MENU: {
			game->PopState();
		}
			return;
		case UI::ACTION::LOAD: {
			m_Level = std::make_unique<Level>(m_UI->GetID(), m_Level.get());
			// TODO Fix camera rotation when loading new level.
			m_Camera->Target(m_Level->GetPosition());
		}
			break;
		case UI::ACTION::SAVE: {
			LevelSaver save(m_Level.get());
		}
			break;
		case UI::ACTION::TOGGLE: {
			m_Level->ToggleMode();
		}
			break;
		case UI::ACTION::ADD_COLOUR: {
			m_Level->AddColour(m_UI->GetColour());
		}
			break;
		case UI::ACTION::EXIT: {
			game->Quit();
		}
			return;
		}

		m_Camera->Update();
		m_Level->Update();
		m_UI->Update();
	}

	void StateEditor::Render() const
	{
		m_Renderer->Clear();

		m_RendererGrid->Render(m_Grid->GetMesh());
		m_Renderer->Render(m_Level->GetMesh());
		m_Renderer->Render(m_UI.get());

		m_Renderer->Swap();
	}
}