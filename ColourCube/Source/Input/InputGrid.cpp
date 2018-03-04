#include "InputGrid.h"
#include "../Camera/CameraBase.h"

namespace Input
{
	InputGrid::InputGrid(GLFWwindow* window, MousePicker* mousePicker)
		: m_Window(window), m_MousePicker(mousePicker)
	{

	}

	void InputGrid::HandleEvents()
	{
		m_MousePicker->HandleEvents();

		for (auto& key : m_Keys)
			key.Pressed = glfwGetKey(m_Window, key.ID);
	}

	void InputGrid::Update(Entity& entity)
	{
		m_MousePicker->Update(entity);

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