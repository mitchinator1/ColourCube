#include "StateMenu.h"
#include "StateGame.h"
#include "../Input/InputCamera.h"
#include "../Camera/CameraBase.h"
#include "../Renderer/RendererMaster.h"
#include "../UI/Font/FontType.h"

#include <iostream>

State::StateMenu::StateMenu()
	: m_Camera(nullptr), m_Renderer(nullptr), m_UI(nullptr)
{
	
}

State::StateMenu::~StateMenu()
{
	
}

void State::StateMenu::Init(GLFWwindow* window)
{
	m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(window));
	m_Renderer = std::make_unique<Renderer::RendererMaster>(window, m_Camera);
	m_UI = std::make_unique<UI::UIMaster>();

	m_UI->AddText("Arial", std::make_unique<UI::UIText>( "Colour Cube!", 4.0f, 0.0f, 5.0f ));
	m_UI->AddButton("Arial", "Play",		40.0f, 50.0f, 20.0f, 10.0f, { 1.0f, 0.6f, 1.0f });
	m_UI->AddButton("Arial", "Editor",		40.0f, 60.0f, 20.0f, 10.0f, { 0.8f, 0.7f, 0.9f });
	m_UI->AddButton("Arial", "Settings",	40.0f, 70.0f, 20.0f, 10.0f,	{ 0.5f, 0.8f, 0.6f });
	m_UI->AddButton("Arial", "Exit",		40.0f, 80.0f, 20.0f, 10.0f, { 0.3f, 0.7f, 0.9f });
	m_UI->UpdateText();
}

void State::StateMenu::Pause()
{
	
}

void State::StateMenu::Resume()
{
	
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

	m_Renderer->Render(*m_UI);

	m_Renderer->Swap();
}
