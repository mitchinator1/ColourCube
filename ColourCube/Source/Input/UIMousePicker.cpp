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

	UI::ACTION UIMousePicker::GetAction(std::unordered_map<UI::TYPE, ElementList>& elements)
	{
		for (auto& box : elements[UI::TYPE::TEXTBOX])
		{
			if (BoxInRange(box->minX, box->minY, box->maxX, box->maxY))
				return box->OnMouseDown();
		}
		for (auto& box : elements[UI::TYPE::BUTTON])
		{
			if (BoxInRange(box->minX, box->minY, box->maxX, box->maxY))
				return box->OnMouseDown();
		}
		return UI::ACTION::NONE;
	}
	
	void UIMousePicker::Highlight(ElementList& buttons, ElementList& elements)
	{
		unsigned int index = 0;
		for (auto& box : elements)
		{
			if (BoxInRange(box->minX, box->minY, box->maxX, box->maxY))
			{
				buttons[index]->OnMouseOver();
			}
			else
			{
				buttons[index]->OnMouseOut();
			}
			++index;
		}
	}

	void UIMousePicker::MoveSlider(ElementList& sliders, ElementList& elements)
	{
		unsigned int index = 0;
		for (auto& box : elements)
		{
			if (box->IsHidden())
			{
				++index;
				continue;
			}

			if (BoxInRange(box->minX, box->minY, box->minX + sliders[index]->GetWidth(), box->maxY))
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

	bool UIMousePicker::BoxInRange(float minX, float minY, float maxX, float maxY)
	{
		if (mouseX >= minX && mouseY <= minY &&
			mouseX <= maxX && mouseY >= maxY)
		{
			return true;
		}

		return false;
	}
}