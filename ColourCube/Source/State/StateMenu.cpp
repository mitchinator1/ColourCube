#include "StateMenu.h"
#include "../Input/InputCamera.h"

#include <iostream>

State::StateMenu::StateMenu()
	: m_Camera(nullptr), m_Renderer(nullptr), m_Button(nullptr)
{
	
}

State::StateMenu::~StateMenu()
{

}

void State::StateMenu::Init(GLFWwindow* window)
{
	m_Font = std::make_shared<Text::FontType>("Arial");
	m_Texts.emplace_back(new Text::GUIText("Menu!", 4.0f, m_Font, { 0.0f, 0.0f }, 1.0f, true));

	m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(window));
	m_Renderer = std::make_unique<Renderer::RendererMaster>(window, m_Camera);

	m_Button = new UI::UIButton({ { "Button", 2.0f, m_Font,{ 0.0f, 0.5f }, 1.0f, true }, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
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

	if (glfwGetKey(game->GetWindow(), GLFW_KEY_Y) == GLFW_PRESS)
		game->PopState();

}

void State::StateMenu::Update(GameEngine* game)
{

}

void State::StateMenu::Render()
{
	m_Renderer->Clear();

	m_Renderer->PrepareText();
	for (auto* text : m_Texts)
		m_Renderer->Render(text);

	m_Renderer->Render(m_Button->GetText());
	m_Renderer->EndRenderingText();

	m_Renderer->Swap();
}
