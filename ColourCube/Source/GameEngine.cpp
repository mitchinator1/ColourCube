#include "GameEngine.h"
#include <iostream>
#include "State/StateBase.h"
#include "GLFW/glfw3.h"
#include "Display.h"

GameEngine::GameEngine(const std::string& title, float width, float height)
	: m_Running(false), m_Display(std::make_shared<Display>(title, width, height))
{
	Init();
}

GameEngine::~GameEngine()
{
	while (!m_States.empty())
		m_States.pop_back();

	glfwTerminate();
}

void GameEngine::Init()
{
	if (!glfwInit())
	{
		std::cout << "GLFW not initialized." << std::endl;
		glfwTerminate();
	}

	if (!m_Display->Init())
	{
		std::cout << "Window not created." << '\n';
	}

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Error!" << std::endl;
	}

	m_Running = true;
}

void GameEngine::ChangeState(std::unique_ptr<State::StateBase> state)
{
	if (!m_States.empty())
		m_States.pop_back();

	m_States.emplace_back(std::move(state));
	m_States.back()->Init(m_Display);
}

void GameEngine::PushState(std::unique_ptr<State::StateBase> state)
{
	if (!m_States.empty())
		m_States.back()->Pause();

	m_States.emplace_back(std::move(state));
	m_States.back()->Init(m_Display);
}

void GameEngine::PopState()
{
	if (m_States.size() > 1)
		m_States.pop_back();
	
	if (!m_States.empty())
		m_States.back()->Resume();
}

void GameEngine::HandleEvents()
{
	glfwPollEvents();

	m_States.back()->HandleEvents(this);
}

void GameEngine::Update()
{
	m_States.back()->Update(this);
}

void GameEngine::Render()
{
	m_States.back()->Render();
}

void GameEngine::Quit()
{
	glfwSetWindowShouldClose(m_Display->Window, true);
	m_Running = false;
}