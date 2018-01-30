#include "GridInput.h"
#include <iostream>

GridInput::GridInput(GLFWwindow* window)
	: m_Window(window)
{

}

void GridInput::HandleEvents()
{
	for (unsigned int i = 0; i < m_Keys.size(); i++)
		m_Keys[i].Pressed = glfwGetKey(m_Window, m_Keys[i].ID);
}

void GridInput::Update(Entity& entity)
{
	if (GetKey(GLFW_KEY_E).Pressed)
		std::cout << "Works" << std::endl;
}

Key& GridInput::GetKey(int key)
{
	for (unsigned int i = 0; i < m_Keys.size(); i++)
		if (m_Keys[i].ID == key)
			return m_Keys[i];
}

