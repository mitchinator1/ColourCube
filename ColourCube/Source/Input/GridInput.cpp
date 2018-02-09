#include "GridInput.h"

GridInput::GridInput(GLFWwindow* window)
	: m_Window(window)
{

}

void GridInput::HandleEvents()
{
	for (auto& key : m_Keys)
		key.Pressed = glfwGetKey(m_Window, key.ID);
}

void GridInput::Update(Entity& entity)
{
	for (auto& key : m_Keys)
		if (!key.Pressed)
			continue;
		else
			if (key.Toggled < glfwGetTime() - 0.5f)
			{
				key.Toggled = (float)glfwGetTime();
				entity.Action(key.Action);
			}
}
