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
			m_Toggled = false;
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
				if (box->InRange((float)mouseX, (float)mouseY))
					return box->OnMouseOver();
		}
		UI::ACTION action = UI::ACTION::NONE;
		/*for (auto& box : elements[UI::TYPE::BUTTON])
		{
			if (!box->IsHidden())
			{
				if (BoxInRange(box->minX, box->minY, box->minX + box->GetWidth(), box->minY + box->GetHeight()))
				{
					std::cout << box->minY + box->GetHeight() << '\n';
					action = box->OnMouseOver();
				}
				else if (box->IsMouseOver())
				{
					action = box->OnMouseOut();
				}
				for (auto& element : box->GetElements())
				{
					if (BoxInRange(element->minX, element->minY, element->GetWidth(), element->GetHeight()))
					{
						action = element->OnMouseOver();
					}
					else if (element->IsMouseOver())
					{
						action = element->OnMouseOut();
					}
				}
			}
		}*/
		return action;
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
	
	void UIMousePicker::HighlightElement(ElementList& elements)
	{
		for (auto& box : elements)
		{
			if (box->IsHidden()) continue; 

			if (box->InRange((float)mouseX, (float)mouseY))
			{
				box->OnMouseOver();
				HighlightElement(box->GetElements());
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