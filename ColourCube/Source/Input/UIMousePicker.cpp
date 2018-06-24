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

		CheckMouseOver(ui);

		if (m_Held)
		{
			CheckMouseDown(ui);
		}
		else
		{
			CheckMouseUp(ui);
		}

	}

	void UIMousePicker::CheckMouseOver(UI::UIMaster* ui)
	{
		auto action = UI::ACTION::NONE;
		for (auto& element : ui->GetElements())
		{
			if (element->IsHidden()) continue;

			if (element->InRange((float)mouseX, (float)mouseY))
			{
				action = element->OnMouseOver();
				action = CheckMouseOver(element->GetElements());
			}
			else if (element->IsMouseOver()) //If not in range, but previously was
			{
				action = element->OnMouseOut();
			}
		}

		ui->SetAction(action);
	}

	UI::ACTION UIMousePicker::CheckMouseOver(ElementList& elements)
	{
		auto action = UI::ACTION::NONE;
		for (auto& element : elements)
		{
			if (element->IsHidden()) continue;

			if (element->InRange((float)mouseX, (float)mouseY))
			{
				action = element->OnMouseOver();
				action = CheckMouseOver(element->GetElements());
			}
			else if (element->IsMouseOver()) //If not in range, but previously was
			{
				action = element->OnMouseOut();
			}
		}

		return action;
	}
	
	void UIMousePicker::CheckMouseDown(UI::UIMaster* ui)
	{
		for (auto& element : ui->GetElements())
		{
			if (element->IsMouseOver())
			{
				auto action = element->OnMouseDown();
				if (m_Toggled)
				{
					ui->SetAction(action);
					return;
				}
				else
				{
					break; //If mouse isn't toggled, break for loop
				}
			}
		}
	}

	void UIMousePicker::CheckMouseUp(UI::UIMaster* ui)
	{
		for (auto& element : ui->GetElements())
		{
			if (element->IsMouseDown())
			{
				auto id = element->GetID();
				auto action = element->OnMouseUp();
				ui->Reveal(id);
				ui->SetID(id);
				ui->SetAction(action);
				return;
			}
		}
	}
	
}