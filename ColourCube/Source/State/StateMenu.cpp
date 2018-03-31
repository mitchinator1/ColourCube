#include "StateMenu.h"
#include "StateGame.h"
#include "../Input/InputCamera.h"
#include "../Camera/CameraBase.h"
#include "../Renderer/RendererMaster.h"
#include "../UI/Font/FontType.h"

State::StateMenu::StateMenu()
	: m_Camera(nullptr), m_Renderer(nullptr)
{
	
}

State::StateMenu::~StateMenu()
{

}

void State::StateMenu::Init(GLFWwindow* window)
{
	m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(window));
	m_Renderer = std::make_unique<Renderer::RendererMaster>(window, m_Camera);

	m_Font = std::make_shared<Text::FontType>("Arial");

	m_UI.AddText(m_Font, UI::UIText("Colour Cube!", 4.0f, m_Font, 0.0f, 5.0f));
	m_UI.AddButton(UI::UIButton{ { "Play",		3.0f, m_Font, 0.0f, 50.0f } });
	m_UI.AddButton(UI::UIButton{ { "Editor",	3.0f, m_Font, 0.0f, 60.0f } });
	m_UI.AddButton(UI::UIButton{ { "Settings",	2.0f, m_Font, 0.0f, 70.0f } });
	m_UI.AddButton(UI::UIButton{ { "Exit",		2.0f, m_Font, 0.0f, 80.0f } });

	m_UI.CalculateMesh();
}

void State::StateMenu::Pause()
{

}

void State::StateMenu::Resume()
{

}

void State::StateMenu::HandleEvents(GameEngine* game)
{
	if (glfwGetKey(game->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(game->GetWindow()))
		game->Quit();

	if (glfwGetKey(game->GetWindow(), GLFW_KEY_T) == GLFW_PRESS)
		game->PushState(std::make_unique<StateGame>());

	if (glfwGetKey(game->GetWindow(), GLFW_KEY_Y) == GLFW_PRESS)
		game->PopState();

}

void State::StateMenu::Update(GameEngine* game)
{

}

void State::StateMenu::Render()
{
	m_Renderer->Clear();

	m_Renderer->Render(&m_UI);

	m_Renderer->Swap();
}
