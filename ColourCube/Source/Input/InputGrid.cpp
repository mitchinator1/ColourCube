#include "InputGrid.h"

namespace Input
{
	InputGrid::InputGrid(GLFWwindow* window)
		: m_Window(window)
	{

	}

	InputGrid::~InputGrid()
	{

	}

	void InputGrid::HandleEvents(Entity& entity)
	{
		for (auto& key : m_Keys)
			key.Pressed = glfwGetKey(m_Window, key.ID);
	}

	void InputGrid::Update(Entity& entity)
	{
		for (auto& key : m_Keys)
			if (!key.Pressed)
				continue;
			else if (key.Toggled < glfwGetTime() - 0.4f)
			{
				key.Toggled = (float)glfwGetTime();
				entity.Action(key.Action);
			}
	}
}