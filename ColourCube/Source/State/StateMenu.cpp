#include "StateMenu.h"
#include "../Input/InputCamera.h"

#include <iostream>

State::StateMenu::StateMenu()
	: m_Camera(nullptr), m_Renderer(nullptr)
{
	
}

State::StateMenu::~StateMenu()
{

}

void State::StateMenu::Init(GLFWwindow* window)
{
	m_Font = std::make_shared<Text::FontType>("Arial");
	m_Texts.emplace_back(new Text::GUIText("Menu!", 4.0f, m_Font, { 0.0f, 0.0f }, 100.0f, true));

	m_Camera = std::make_shared<Camera::CameraBase>(std::make_unique<Input::InputCamera>(window));
	m_Renderer = std::make_unique<Renderer::RendererMaster>(window, m_Camera);

	m_Buttons.emplace_back(UI::UIButton{ { "Play", 2.0f, m_Font,{ 0.0f, 50.0f } }, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f });
	m_Buttons.emplace_back(UI::UIButton{ { "Editor", 2.0f, m_Font,{ 0.0f, 60.0f } },{ 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f }, 0.0f });
	m_Buttons.emplace_back(UI::UIButton{ { "Settings", 2.0f, m_Font,{ 0.0f, 70.0f } },{ 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f }, 0.0f });
	m_Buttons.emplace_back(UI::UIButton{ { "Exit", 2.0f, m_Font,{ 0.0f, 80.0f } },{ 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f }, 0.0f });

	m_UIMaster.AddBackground(UI::UIBackground{ {-0.15f, -0.2f}, 0.3f });
	m_UIMaster.CalculateMesh();

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

	m_Renderer->PrepareUI();
	m_Renderer->Render(&m_UIMaster);
	m_Renderer->EndRenderingUI();

	m_Renderer->PrepareText();
	for (auto* text : m_Texts)
		m_Renderer->Render(text);

	for (auto& button : m_Buttons)
		m_Renderer->Render(button.GetText());
	m_Renderer->EndRenderingText();

	m_Renderer->Swap();
}
