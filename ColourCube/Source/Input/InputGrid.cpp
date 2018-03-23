#include "InputGrid.h"

namespace Input
{
	InputGrid::InputGrid(GLFWwindow* window, std::unique_ptr<MousePicker> mousePicker)
		: m_Window(window), m_MousePicker(std::move(mousePicker))
	{

	}

	InputGrid::~InputGrid()
	{

	}

	void InputGrid::HandleEvents(Entity& entity)
	{
		m_MousePicker->HandleEvents(entity);

		for (auto& key : m_Keys)
			key.Pressed = glfwGetKey(m_Window, key.ID);
	}

	void InputGrid::Update(Entity& entity)
	{
		m_MousePicker->Update(entity);

		for (auto& key : m_Keys)
			if (!key.Pressed)
				continue;
			else if (key.Toggled < glfwGetTime() - 0.5f)
			{
				key.Toggled = (float)glfwGetTime();
				entity.Action(key.Action);
			}
	}
}