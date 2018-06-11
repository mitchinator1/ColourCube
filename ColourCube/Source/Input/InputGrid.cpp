#include "InputGrid.h"
#include "GLFW/glfw3.h"
#include "../Entity.h"

namespace Input
{
	InputGrid::InputGrid(std::shared_ptr<Display>& display)
		: InputBase(display)
	{
		m_Keys = { 
			{ GLFW_KEY_E,	Command::CHANGE_COLOUR }
		};
	}

	InputGrid::~InputGrid()
	{

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