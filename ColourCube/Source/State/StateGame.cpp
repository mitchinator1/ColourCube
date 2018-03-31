#include "StateGame.h"
#include "GL/glew.h"
#include "StateMenu.h"

#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"

#include "../Input/InputCamera.h"
#include "../Input/InputGrid.h"
#include "../Input/MousePicker.h"

#include "../UI/UIText.h"
#include "../UI/Font/FontType.h"

#include "../Entity.h"
#include "../Level.h"

namespace State
{
	StateGame::StateGame()
		: m_Level(nullptr), m_Camera(nullptr), m_Renderer(nullptr), m_Font(nullptr)
	{

	}

	StateGame::~StateGame()
	{
		delete m_Level;
	}

	void StateGame::Init(GLFWwindow* window)
	{
		m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(window));
		m_Level = new Level(std::make_unique<Input::InputGrid>(window, std::make_unique<Input::MousePicker>(m_Camera, window)));
		m_Camera->Target(m_Level);

		m_Font = std::make_shared<Text::FontType>("Arial");

		m_Renderer = std::make_unique<Renderer::RendererMaster>(window, m_Camera);

		//m_Entities.emplace_back(m_Camera);
		m_Entities.emplace_back(m_Level);
		m_Texts.emplace_back(new UI::UIText("Text that expands onto multiple lines!", 4.0f, m_Font, 0.01f, 0.0f, 100.0f, false));
		m_Texts.emplace_back(new UI::UIText("Test Smaller Text", 2.0f, m_Font, 0.0f, 70.0f));
	}

	void StateGame::Pause()
	{

	}

	void StateGame::Resume()
	{

	}

	void StateGame::HandleEvents(GameEngine* game)
	{
		if (glfwGetKey(game->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(game->GetWindow()))
			game->Quit();

		if (glfwGetKey(game->GetWindow(), GLFW_KEY_T) == GLFW_PRESS)
			game->PushState(std::make_unique<StateMenu>());

		if (glfwGetKey(game->GetWindow(), GLFW_KEY_Y) == GLFW_PRESS)
			game->PopState();

		m_Camera->HandleEvents();

		for (const auto& entity : m_Entities)
			entity->HandleEvents();
	}

	void StateGame::Update(GameEngine* game)
	{
		m_Camera->Update();

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

		/*m_Renderer->PrepareText();
		for (auto* text : m_Texts)
			m_Renderer->Render(text);
		m_Renderer->EndRenderingText();
*/
		m_Renderer->Swap();
	}

}