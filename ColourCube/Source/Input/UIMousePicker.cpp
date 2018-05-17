#include "UIMousePicker.h"
#include "../Display.h"
#include "../UI/UIElement.h"
#include "GLFW/glfw3.h"

namespace Input
{
	UIMousePicker::UIMousePicker() noexcept
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
		
		if (glfwGetMouseButton(display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_ToggledTime < glfwGetTime() - DELAY)
		{
			m_ToggledTime = (float)glfwGetTime();
			m_Toggled = true;
			m_Held = true;
		}
		else if (glfwGetMouseButton(display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			m_Held = false;
		}
		else
		{
			m_Toggled = false;
		}
	}

	UI::ACTION UIMousePicker::GetMouseOver(std::unordered_map<UI::TYPE, ElementList>& elements)
	{
		for (auto& box : elements[UI::TYPE::TEXTBOX])
		{
			if (!box->IsHidden())
				if (BoxInRange(box->minX, box->minY, box->maxX, box->maxY))
					return box->OnMouseOver();
		}
		for (auto& box : elements[UI::TYPE::BUTTON])
		{
			if (!box->IsHidden())
				if (BoxInRange(box->minX, box->minY, box->maxX, box->maxY))
				{
					return box->OnMouseOver();
				}
		}
		return UI::ACTION::NONE;
	}

	UI::ACTION UIMousePicker::GetMouseDown(std::unordered_map<UI::TYPE, ElementList>& elements)
	{
		for (auto& box : elements[UI::TYPE::TEXTBOX])
		{
			if (!box->IsHidden())
				if (BoxInRange(box->minX, box->minY, box->maxX, box->maxY))
					return box->OnMouseDown();
		}
		for (auto& box : elements[UI::TYPE::BUTTON])
		{
			if (!box->IsHidden())
				if (BoxInRange(box->minX, box->minY, box->maxX, box->maxY))
				{
					return box->OnMouseDown();
				}
		}
		return UI::ACTION::NONE;
	}
	
	void UIMousePicker::HighlightElement(ElementList& elements)
	{
		for (auto& box : elements)
		{
			if (box->IsHidden())
			{
				continue;
			}
			if (BoxInRange(box->minX, box->minY, box->maxX, box->maxY))
			{
				box->OnMouseOver();
			}
			else
			{
				box->OnMouseOut();
			}
		}
	}

	bool UIMousePicker::MoveElement(ElementList& elements)
	{
		for (auto& element : elements)
		{
			if (element->IsHidden())
			{
				continue;
			}

			if (BoxInRange(element->minX, element->minY, element->minX + element->GetWidth(), element->maxY))
			{
				float newX = (float)mouseX - element->minX;

				element->SetValue(newX / element->GetWidth());
				return true;
			}
		}
		return false;
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