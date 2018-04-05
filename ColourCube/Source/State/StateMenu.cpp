#include "StateMenu.h"
#include "StateGame.h"
#include "../Input/InputCamera.h"
#include "../Camera/CameraBase.h"
#include "../Renderer/RendererMaster.h"
#include "../UI/Font/FontType.h"

#include <iostream>

State::StateMenu::StateMenu()
	: m_Camera(nullptr), m_Renderer(nullptr)
{
	
}

State::StateMenu::~StateMenu()
{
	//std::cout << "StateMenu Delete Called" << std::endl;
}

void State::StateMenu::Init(GLFWwindow* window)
{
	m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(window));
	m_Renderer = std::make_unique<Renderer::RendererMaster>(window, m_Camera);

	m_UI.AddText("Arial", { "Colour Cube!", 4.0f, 0.0f, 5.0f });
	m_UI.AddButton("Arial", UI::UIButton{ { "Play",		3.0f, 0.0f, 50.0f } });
	m_UI.AddButton("Arial", UI::UIButton{ { "Editor",	3.0f, 0.0f, 60.0f } });
	m_UI.AddButton("Arial", UI::UIButton{ { "Settings",	2.0f, 0.0f, 70.0f } });
	m_UI.AddButton("Arial", UI::UIButton{ { "Exit",		2.0f, 0.0f, 80.0f } });

	m_UI.UpdateText();
}

void State::StateMenu::Pause()
{
	//std::cout << "Pause Menu" << std::endl;
}

void State::StateMenu::Resume()
{
	//std::cout << "Resume Menu" << std::endl;
}

void State::StateMenu::HandleEvents(GameEngine* game)
{
	if (glfwGetKey(game->GetWindow(), GLFW_KEY_T) == GLFW_PRESS)
		game->PushState(std::make_unique<StateGame>());

	if (glfwGetKey(game->GetWindow(), GLFW_KEY_Y) == GLFW_PRESS)
		game->PopState();

	if (glfwGetKey(game->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(game->GetWindow()))
		game->Quit();

}

void State::StateMenu::Update(GameEngine* game)
{

}

void State::StateMenu::Render()
{
	m_Renderer->Clear();

	m_Renderer->Render(m_UI);

	m_Renderer->Swap();
}
