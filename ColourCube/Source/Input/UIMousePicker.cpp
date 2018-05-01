#include "UIMousePicker.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "../Display.h"
#include "../UI/UIBackground.h"

namespace Input
{
	UIMousePicker::UIMousePicker()
		: mouseX(0.0), mouseY(0.0)
	{
		
	}

	UIMousePicker::~UIMousePicker()
	{

	}

	void UIMousePicker::HandleEvents(std::shared_ptr<Display> display)
	{
		glfwGetCursorPos(display->Window, &mouseX, &mouseY);
		mouseX = (mouseX / display->Width) * 2.0f - 1.0f;
		mouseY = (mouseY / display->Height) * 2.0f - 1.0f;
		
		if (glfwGetMouseButton(display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_ToggledTime < glfwGetTime() - 0.15f)
		{
			m_ToggledTime = (float)glfwGetTime();
			m_Toggled = true;
		}
		else
		{
			m_Toggled = false;
		}
	}

	ACTION UIMousePicker::GetAction(std::unordered_map<UI::TYPE, std::vector<std::unique_ptr<UI::UIHitBox>>>& hitBoxes)
	{
		for (auto& box : hitBoxes[UI::TYPE::TEXTBOX])
		{
			if (mouseX > box->xMin && mouseY > box->yMin &&
				mouseX < box->xMax && mouseY < box->yMax)
				return box->Action;
		}
		for (auto& box : hitBoxes[UI::TYPE::BUTTON])
		{
			if (mouseX > box->xMin && mouseY > box->yMin &&
				mouseX < box->xMax && mouseY < box->yMax)
				return box->Action;
		}
		return ACTION::NONE;
	}

	void UIMousePicker::Highlight(std::vector<std::unique_ptr<UI::UIBackground>>& backgrounds, std::vector<std::unique_ptr<UI::UIHitBox>>& hitBoxes)
	{
		unsigned int index = 0;
		for (auto& box : hitBoxes)
		{
			if (mouseX > box->xMin && mouseY > box->yMin &&
				mouseX < box->xMax && mouseY < box->yMax)
			{
				backgrounds[index]->SetAlpha(0.5f);
			}
			else
			{
				backgrounds[index]->SetAlpha(1.0f);
			}
			++index;
		}
	}

	void UIMousePicker::MoveSlider(std::vector<std::unique_ptr<UI::UIBackground>>& sliders, std::vector<std::unique_ptr<UI::UIHitBox>>& hitBoxes)
	{
		unsigned int index = 0;
		for (auto& box : hitBoxes)
		{
			if (mouseX >= box->xMin && mouseY >= box->yMin &&
				mouseX <= box->xMax && mouseY <= box->yMax)
			{
				auto numerator = (float)mouseX - box->xMin;
				auto denominator = box->xMax - box->xMin;
				sliders[index]->SetPosition({ (float)mouseX - box->xMin - 0.008f, 0.0f, 0.0f });
				sliders[index]->SetAlpha(numerator / denominator);
			}
			++index;
		}
	}
}