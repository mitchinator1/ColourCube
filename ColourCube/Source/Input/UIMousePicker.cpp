#include "UIMousePicker.h"
#include "../Display.h"
#include "../UI/UIElement.h"
#include "../UI/UIMaster.h"

namespace Input
{
	UIMousePicker::UIMousePicker() noexcept
	{
		
	}

	UIMousePicker::~UIMousePicker()
	{

	}

	void UIMousePicker::HandleEvents(std::shared_ptr<Display> display, UI::UIMaster* ui)
	{
		glfwGetCursorPos(display->Window, &mouseX, &mouseY);
		mouseX = (mouseX / display->Width) * 100.0f;
		mouseY = (mouseY / display->Height) * 100.0f;

		ui->SetAction(GetMouseOver(ui->GetElements()));

		if (glfwGetMouseButton(display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_ToggledTime < glfwGetTime() - DELAY)
		{
			m_ToggledTime = (float)glfwGetTime();
			m_Toggled = true;
			m_Held = true;
			ui->SetAction(GetMouseDown(ui));
		}
		else if (glfwGetMouseButton(display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			m_Held = false;
			m_Toggled = false;
			ui->SetAction(GetMouseUp(ui->GetElements()));
		}
		else
		{
			m_Toggled = false;
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
				return action;
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

}