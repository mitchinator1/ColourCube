#include "CameraInput.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include <iostream>

CameraInput::CameraInput(GLFWwindow* window)
	: m_Window(window)
{

}

CameraInput::~CameraInput()
{

}

void CameraInput::HandleEvents()
{
	for (unsigned int i = 0; i < m_Keys.size(); i++)
		m_Keys[i].Pressed = glfwGetKey(m_Window, m_Keys[i].ID);
}

void CameraInput::Update(Entity& entity)
{
	for (unsigned int i = 0; i < m_Keys.size(); i++)
		if (!m_Keys[i].Pressed)
			continue;
		else
			entity.Action(m_Keys[i].Action);
}

Key& CameraInput::GetKey(int key)
{
	for (unsigned int i = 0; i < m_Keys.size(); i++)
		if (m_Keys[i].ID == key)
			return m_Keys[i];
}
