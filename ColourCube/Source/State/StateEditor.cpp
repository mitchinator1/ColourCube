#include "StateEditor.h"
#include "../Input/EditorMousePicker.h"
#include "../Input/MousePicker.h"
#include "../Input/InputCamera.h"

#include "../Renderer/RendererMaster.h"
#include "../Renderer/RendererGrid.h"

#include "../Level/Level.h"
#include "../Level/Gridline.h"
#include "../Level/LevelSaver.h"

namespace State
{
	StateEditor::StateEditor(std::shared_ptr<Display>& display)
		: StateBase(display)
		, m_RendererGrid(std::make_unique<Renderer::RendererGrid>(m_Camera))
		, m_Level(std::make_unique<Level>(0, std::make_unique<Input::EditorMousePicker>(m_Camera, display)))
		, m_Grid(std::make_unique<Gridline>())
	{
		m_Camera->AddInput(std::make_unique<Input::InputCamera>(display));
		m_Camera->Target(m_Level->position);
		m_UI->Build("Editor");
	}

	StateEditor::~StateEditor()
	{

	}
	
	void StateEditor::HandleEvents(GameEngine* game)
	{
		if (!m_UI->HandleEvents(m_Display))
		{
			m_Level->HandleEvents();
		}
		m_Camera->HandleEvents();

		if (glfwGetKey(m_Display->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Display->Window))
		{
			game->Quit();
		}
	}

	void StateEditor::Update(GameEngine* game)
	{
		switch (m_UI->GetAction())
		{
		case UI::ACTION::MENU:			{
			game->PopState();
			return;
		}
		case UI::ACTION::LOAD:			{
			m_Level = std::make_unique<Level>(m_UI->GetLevelNumber(), m_Level.get());
			m_Camera->Target(m_Level->position);
			break;
		}
		case UI::ACTION::SAVE:			{
			LevelSaver save(m_Level.get());
			break;
		}
		case UI::ACTION::TOGGLE:		{
			m_Level->ToggleMode(MOVE_TYPE::PLACE);
			break;
		}
		case UI::ACTION::ADD_COLOUR:	{
			m_Level->AddColour(m_UI->GetColour());
			break;
		}
		case UI::ACTION::UNDO:			{
			m_Level->Undo();
			break;
		}
		case UI::ACTION::REDO:			{
			m_Level->Redo();
			break;
		}
		case UI::ACTION::NEXT_STEP:		{
			m_UI->Build("EditorColours");
			m_Level->ChangeMouseInput(std::make_unique<Input::MousePicker>(m_Camera, m_Display));
			break;
		}
		case UI::ACTION::PREV_STEP:		{
			m_UI->Build("Editor");
			m_Level->ChangeMouseInput(std::make_unique<Input::EditorMousePicker>(m_Camera, m_Display));
			m_Level->RemoveColours();
			break;
		}
		case UI::ACTION::EXIT:			{
			game->Quit();
			return;
		}
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