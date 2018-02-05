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
	for (unsigned int i = 0; i < m_Keys.size(); i++)
		if (!GetKey(m_Keys[i].ID).Pressed)
			continue;
		else
			if (GetKey(m_Keys[i].ID).Toggled < glfwGetTime() - 0.5f)
			{
				m_Keys[i].Toggled = glfwGetTime();
				entity.Action(m_Keys[i].Action);
			}
}

Key& GridInput::GetKey(int key)
{
	for (unsigned int i = 0; i < m_Keys.size(); i++)
		if (m_Keys[i].ID == key)
			return m_Keys[i];
}

