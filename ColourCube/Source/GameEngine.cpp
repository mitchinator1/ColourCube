#include "GameEngine.h"
#include <iostream>
#include "States/BasicState.h"

GameEngine::GameEngine(const std::string& title, int width, int height)
	: m_Running(false), m_Title(title), m_Width(width), m_Height(height)
{
	Init();
}

GameEngine::~GameEngine()
{
	while (!m_States.empty())
	{
		m_States.back()->~BasicState();
		m_States.pop_back();
	}

	glfwTerminate();
}

void GameEngine::Init()
{
	if (!glfwInit())
	{
		std::cout << "GLFW not initialized." << std::endl;
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		std::cout << "Window not created." << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_Window);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;

	m_Running = true;
}

void GameEngine::ChangeState(BasicState* state)
{
	if (!m_States.empty())
	{
		m_States.back()->~BasicState();
		m_States.pop_back();
	}

	m_States.push_back(state);
	m_States.back()->Init(m_Window);
}

void GameEngine::PushState(BasicState* state)
{
	if (!m_States.empty())
		m_States.back()->Pause();

	m_States.push_back(state);
	m_States.back()->Init(m_Window);
}

void GameEngine::PopState()
{
	if (!m_States.empty())
	{
		m_States.back()->~BasicState();
		m_States.pop_back();
	}
	
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

void GameEngine::Draw()
{
	m_States.back()->Draw(this);

	glfwSwapBuffers(m_Window);
}

void GameEngine::Quit()
{
	glfwSetWindowShouldClose(m_Window, true);
	m_Running = false;
}