#include "CameraInput.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include <iostream>

CameraInput::CameraInput()
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
	if (GetKey(GLFW_KEY_W).Pressed)
		entity.Move(MOVEMENT::FORWARD);

	if (GetKey(GLFW_KEY_S).Pressed)
		entity.Move(MOVEMENT::BACKWARD);
	
	if (GetKey(GLFW_KEY_A).Pressed)
		entity.Move(MOVEMENT::LEFT);

	if (GetKey(GLFW_KEY_D).Pressed)
		entity.Move(MOVEMENT::RIGHT);

	if (GetKey(GLFW_KEY_SPACE).Pressed)
		entity.Move(MOVEMENT::UP);

	if (GetKey(GLFW_KEY_LEFT_SHIFT).Pressed)
		entity.Move(MOVEMENT::DOWN);
}

Key& CameraInput::GetKey(int key)
{
	for (unsigned int i = 0; i < m_Keys.size(); i++)
		if (m_Keys[i].ID == key)
			return m_Keys[i];
}

void CameraInput::Bind(GLFWwindow* window)
{
	m_Window = window;
}