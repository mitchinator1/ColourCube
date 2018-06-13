#include "StateEditor.h"

#include "../Input/InputGrid.h"
#include "../Input/EditorMousePicker.h"
#include "../Input/InputCamera.h"

#include "../Camera/CameraBase.h"
#include "../Renderer/RendererMaster.h"
#include "../Renderer/RendererGrid.h"
#include "../UI/UIMaster.h"
#include "../UI/Element/UIText.h"

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
		, m_Level(std::make_unique<Level>("BlankLevel", std::make_unique<Input::InputGrid>(display), std::make_unique<Input::EditorMousePicker>(m_Camera, display)))
		, m_Grid(std::make_unique<Gridline>(5, 5))
	{
		m_Camera->Target(m_Level->GetPosition());
		m_UI->Build("Editor");
		m_UI->Update();
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
			//TODO: Remove Continue function from state
		case UI::ACTION::CONTINUE: {
			m_UI->Continue();
		}
			break;
		case UI::ACTION::MENU: {
			game->PopState();
		}
			return;
		case UI::ACTION::LOAD: {
			m_Level.reset();
			m_Level = std::make_unique<Level>(m_UI->GetID(), 
				std::make_unique<Input::InputGrid>(game->GetDisplay()), 
				std::make_unique<Input::EditorMousePicker>(m_Camera, game->GetDisplay()));
			//TODO: Remove AddText from States
			m_UI->AddText("Arial", m_UI->GetID() + "Alert")
				->SetPosition(0.0f, 50.0f)
				->SetSize(2.75f)
				->SetTime(0.75f)
				->SetCenter(true);
		}
			break;
		case UI::ACTION::SAVE: {
			LevelSaver save(m_Level.get());
			m_UI->AddText("Arial", "EditorAlertSave")
				->SetPosition(0.0f, 50.0f)
				->SetSize(2.75f)
				->SetTime(0.75f)
				->SetCenter(true);
		}
			break;
		case UI::ACTION::TOGGLE: {
			//m_Level->ToggleMode();
			//TODO: Remove AddText from States
			m_UI->AddText("Arial", "EditorAlert")
				->SetPosition(0.0f, 50.0f)
				->SetSize(2.75f)
				->SetTime(0.75f)
				->SetCenter(true)
				->SetKeyNumber(!m_Level->ToggleMode());
		}
			break;
		case UI::ACTION::ADD_COLOUR: {
			m_Level->AddColour(m_UI->GetColour());
			m_UI->AddText("Arial", "EditorAlert")
				->SetPosition(0.0f, 20.0f)
				->SetCenter(true)
				->SetSize(2.5f)
				->SetTime(0.75f)
				->SetKeyNumber(2);
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

		m_RendererGrid->Render(*m_Grid);
		m_Renderer->Render(*m_Level);
		m_Renderer->Render(*m_UI);

		m_Renderer->Swap();
	}
}