#include "UIMousePicker.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "../Display.h"
#include "../UI/UIHitBox.h"

namespace Input
{
	UIMousePicker::UIMousePicker()
	{
		std::cout << "Mouse Picker Created." << std::endl;
	}

	UIMousePicker::~UIMousePicker()
	{

	}

	bool UIMousePicker::GetMouseInput(std::shared_ptr<Display> display)
	{
		if (glfwGetMouseButton(display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_Toggled < glfwGetTime() - 0.15f)
		{
			m_Toggled = (float)glfwGetTime();
			glfwGetCursorPos(display->Window, &mouseX, &mouseY);
			mouseX = (mouseX / display->Width) * 2.0f - 1.0f;
			mouseY = (mouseY / display->Height) * 2.0f - 1.0f;
			return true;
		}
		else
		{
			return false;
		}
	}

	unsigned int UIMousePicker::GetID(std::vector<UI::UIHitBox>& hitBoxes)
	{
		for (auto& box : hitBoxes)
		{
			if (mouseX > box.xMin && mouseY > box.yMin &&
				mouseX < box.xMax && mouseY < box.yMax)
				return box.ID;
		}

		return 0;
	}
}