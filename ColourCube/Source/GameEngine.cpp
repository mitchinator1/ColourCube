#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(const std::string title)
	: m_Title(title)
{
	
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

	m_Window = glfwCreateWindow(1400, 900, m_Title.c_str(), NULL, NULL);
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

void GameEngine::CleanUp()
{
	m_States.clear();
	glfwTerminate();
}

void GameEngine::ChangeState(BasicState* state)
{
	state->Init();
	PushState(state);
}

void GameEngine::PushState(BasicState* state)
{
	m_States.push_back(state);
}

void GameEngine::PopState()
{
	m_States.pop_back();
}

void GameEngine::HandleEvents()
{
	glfwPollEvents();
	if (glfwWindowShouldClose(m_Window))
		m_Running = false;

	m_States[0]->HandleEvents();
}

void GameEngine::Update()
{
	m_States[0]->Update();
}

void GameEngine::Draw()
{
	m_States[0]->Draw();

	glfwSwapBuffers(m_Window);
}
