#include "UIMousePicker.h"
#include "../Display.h"
#include "../UI/UIElement.h"

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
		mouseX = (mouseX / display->Width) * 100.0f;
		mouseY = (mouseY / display->Height) * 100.0f;
		
		if (glfwGetMouseButton(display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_ToggledTime < glfwGetTime() - DELAY)
		{
			m_ToggledTime = (float)glfwGetTime();
			m_Toggled = true;
			m_Held = true;
		}
		else if (glfwGetMouseButton(display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			m_Held = false;
			m_Toggled = false;
		}
		else
		{
			m_Toggled = false;
		}
	}

	UI::ACTION UIMousePicker::GetMouseOver(ElementList& elements)
	{
		for (auto& box : elements)
		{
			if (!box->IsHidden())
				if (box->InRange((float)mouseX, (float)mouseY))
					return box->OnMouseOver();
		}

		return UI::ACTION::NONE;
	}

	UI::ACTION UIMousePicker::GetMouseDown(ElementList& elements)
	{
		/*for (auto& box : elements[UI::TYPE::TEXTBOX])
		{
			if (!box->IsHidden())
				if (BoxInRange(box->minX, box->minY, box->maxX, box->maxY))
				{
					return box->OnMouseDown();
				}
		}*/
		for (auto& box : elements)
		{
			if (box->IsMouseOver())
			{
				return box->OnMouseDown();
			}
		}
		return UI::ACTION::NONE;
	}
	
	void UIMousePicker::CheckMouseOver(ElementList& elements)
	{
		for (auto& box : elements)
		{
			if (box->IsHidden()) continue; 

			if (box->InRange((float)mouseX, (float)mouseY))
			{
				box->OnMouseOver();
				CheckMouseOver(box->GetElements());
			}
			else if (box->IsMouseOver())
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

			if (element->InRange((float)mouseX, (float)mouseY))
			{
				float newX = (float)mouseX - element->minX;

				element->SetValue(newX / element->width);
				return true;
			}
		}
		return false;
	}

}