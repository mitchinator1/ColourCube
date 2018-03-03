#include "InputGrid.h"
#include "../Camera/CameraBasic.h"

namespace Input
{
	Grid::Grid(GLFWwindow* window, MousePicker* mousePicker)
		: m_Window(window), m_MousePicker(mousePicker)
	{

	}

	void Grid::HandleEvents()
	{
		for (auto& key : m_Keys)
			key.Pressed = glfwGetKey(m_Window, key.ID);
	}

	void Grid::Update(Entity& entity)
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
}