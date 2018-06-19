#include "MouseBase.h"

namespace Input
{
	MouseBase::MouseBase(std::shared_ptr<Display>& display)
		: m_Display(display)
	{
	
	}

	void MouseBase::GetMouseInput()
	{
		glfwGetCursorPos(m_Display->Window, &mouseX, &mouseY);

		if (glfwGetMouseButton(m_Display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_ToggledTime < glfwGetTime() - DELAY)
		{
			m_ToggledTime = (float)glfwGetTime();
			m_Toggled = true;
			m_Held = true;
		}
		else if (glfwGetMouseButton(m_Display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			m_Held = false;
			m_Toggled = false;
		}
		else
		{
			m_Toggled = false;
		}
	}

}