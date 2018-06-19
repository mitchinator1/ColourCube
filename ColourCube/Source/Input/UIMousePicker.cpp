#include "UIMousePicker.h"
#include "../Display.h"
#include "../UI/Element/UIElement.h"
#include "../UI/UIMaster.h"

namespace Input
{
	UIMousePicker::UIMousePicker(std::shared_ptr<Display>& display)
		: Mouse2D(display)
	{
		
	}

	UIMousePicker::~UIMousePicker()
	{

	}

	void UIMousePicker::HandleEvents(UI::UIMaster* ui)
	{
		GetMouseInput();
		mouseX = (mouseX / m_Display->Width) * 100.0f;
		mouseY = (mouseY / m_Display->Height) * 100.0f;

		ui->SetAction(GetMouseOver(ui->GetElements()));

		if (m_Held)
		{
			ui->SetAction(GetMouseDown(ui));
		}
		else
		{
			ui->SetAction(GetMouseUp(ui));
		}

	}

	UI::ACTION UIMousePicker::GetMouseOver(ElementList& elements)
	{
		UI::ACTION action = UI::ACTION::NONE;

		for (auto& element : elements)
		{
			if (element->IsHidden()) continue;

			if (element->InRange((float)mouseX, (float)mouseY))
			{
				element->OnMouseOver();
				action = GetMouseOver(element->GetElements());
			}
			else if (element->IsMouseOver()) //If not in range, but previously was
			{
				action = element->OnMouseOut();
			}
		}

		return action;
	}
	
	UI::ACTION UIMousePicker::GetMouseDown(UI::UIMaster* ui)
	{
		for (auto& element : ui->GetElements())
		{
			if (element->IsMouseOver())
			{
				auto action = element->OnMouseDown();
				if (m_Toggled)
				{
					return action;
				}
				else
				{
					break; //If mouse isn't toggled, break for loop
				}
			}
		}

		return UI::ACTION::NONE;
	}

	UI::ACTION UIMousePicker::GetMouseUp(UI::UIMaster* ui)
	{
		for (auto& element : ui->GetElements())
		{
			if (element->IsMouseDown())
			{
				auto id = element->GetID();
				auto action = element->OnMouseUp();
				ui->Reveal(id);
				ui->SetID(id);
				return action;
			}
		}

		return UI::ACTION::NONE;
	}
	
}