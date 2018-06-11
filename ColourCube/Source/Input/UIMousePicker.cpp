#include "UIMousePicker.h"
#include "../Display.h"
#include "../UI/Element/UIElement.h"
#include "../UI/UIMaster.h"

namespace Input
{
	UIMousePicker::UIMousePicker(std::shared_ptr<Display>& display)
		: m_Display(display)
	{
		
	}

	UIMousePicker::~UIMousePicker()
	{

	}

	void UIMousePicker::HandleEvents(UI::UIMaster* ui)
	{
		GetMouseInput();

		ui->SetAction(GetMouseOver(ui->GetElements()));

		if (m_Held)
		{
			ui->SetAction(GetMouseDown(ui));
		}
		else
		{
			ui->SetAction(GetMouseUp(ui->GetElements()));
		}

	}

	UI::ACTION UIMousePicker::GetMouseOver(ElementList& elements)
	{
		UI::ACTION action = UI::ACTION::NONE;

		for (auto& box : elements)
		{
			if (box->IsHidden()) continue;

			if (box->InRange((float)mouseX, (float)mouseY))
			{
				box->OnMouseOver();
				action = GetMouseOver(box->GetElements());
			}
			else if (box->IsMouseOver())
			{
				action = box->OnMouseOut();
			}
		}

		return action;
	}
	
	UI::ACTION UIMousePicker::GetMouseDown(UI::UIMaster* ui)
	{
		for (auto& box : ui->GetElements())
		{
			if (box->IsMouseOver())
			{
				UI::ACTION action = box->OnMouseDown();
				if (action == UI::ACTION::SHOW)
				{
					ui->Reveal(box->GetID());
				}
				if (m_Toggled)
				{
					return action;
				}
				else
				{
					break;
				}
			}
		}

		return UI::ACTION::NONE;
	}

	UI::ACTION UIMousePicker::GetMouseUp(ElementList& elements)
	{
		for (auto& element : elements)
		{
			if (element->IsMouseDown())
			{
				return element->OnMouseUp();
			}
		}

		return UI::ACTION::NONE;
	}

	void UIMousePicker::GetMouseInput()
	{
		glfwGetCursorPos(m_Display->Window, &mouseX, &mouseY);
		mouseX = (mouseX / m_Display->Width) * 100.0f;
		mouseY = (mouseY / m_Display->Height) * 100.0f;

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