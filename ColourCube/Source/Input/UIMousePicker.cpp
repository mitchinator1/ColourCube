#include "UIMousePicker.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "../Display.h"
#include "../UI/UIElement.h"

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
		mouseY = 1.0f - (mouseY / display->Height) * 2.0f;
		
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

	UI::ACTION UIMousePicker::GetAction(std::unordered_map<UI::TYPE, std::vector<std::unique_ptr<UI::UIElement>>>& elements)
	{
		for (auto& box : elements[UI::TYPE::TEXTBOX])
		{
			if (mouseX >= box->minX && mouseY <= box->minY &&
				mouseX <= box->maxX && mouseY >= box->maxY)
				return box->GetAction();
		}
		for (auto& box : elements[UI::TYPE::BUTTON])
		{
			if (mouseX >= box->minX && mouseY <= box->minY &&
				mouseX <= box->maxX && mouseY >= box->maxY)
				return box->GetAction();
		}
		return UI::ACTION::NONE;
	}

	void UIMousePicker::Highlight(std::vector<std::unique_ptr<UI::UIElement>>& buttons, std::vector<std::unique_ptr<UI::UIElement>>& elements)
	{
		unsigned int index = 0;
		for (auto& box : elements)
		{
			if (mouseX >= box->minX && mouseY <= box->minY &&
				mouseX <= box->maxX && mouseY >= box->maxY)
			{
				buttons[index]->SetAlpha(0.5f);
			}
			else
			{
				buttons[index]->SetAlpha(1.0f);
			}
			++index;
		}
	}

	void UIMousePicker::MoveSlider(std::vector<std::unique_ptr<UI::UIElement>>& sliders, std::vector<std::unique_ptr<UI::UIElement>>& elements)
	{
		unsigned int index = 0;
		for (auto& box : elements)
		{
			if (mouseX >= box->minX && mouseY <= box->minY &&
				mouseX <= box->minX + sliders[index]->GetWidth() && mouseY >= box->maxY)
			{
				auto denominator = (box->minX + sliders[index]->GetWidth()) - box->minX;

				auto prevX = sliders[index]->GetPosition().x;
				auto newX = (float)mouseX - box->minX - 0.008f;

				if (abs(newX - prevX) > 0.025f)
					newX = (newX + prevX) / 2.0f;

				sliders[index]->SetValue(newX / denominator);
			}
			++index;
		}
	}
}