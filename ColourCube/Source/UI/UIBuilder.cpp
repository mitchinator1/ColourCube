#include "UIBuilder.h"
#include "UIMaster.h"
#include "Element/UIDropdown.h"
#include "Element/UIButton.h"
#include "Element/UISlider.h"
#include "Element/UIPopup.h"
#include "Element/UIScrollbox.h"
#include "Element/UIText.h"

namespace UI
{
	UIBuilder::UIBuilder(const std::string& filename)
		: m_Filepath("Resources/Data/" + filename + ".xml")
	{
		
	}

	UIBuilder::~UIBuilder()
	{

	}

	void UIBuilder::LoadUI(UIMaster* ui)
	{
		m_Stream.open(m_Filepath);
		std::string line;
		while (std::getline(m_Stream, line, ' '))
		{
			if (line.find("Dropdown") != std::string::npos)
			{
				auto dropdown = BuildDropdown();
				dropdown->Build();
				ui->AddElement<UI::UIDropdown>(dropdown);
				continue;
			}

			if (line.find("Button") != std::string::npos)
			{
				auto button = BuildButton();
				button->Build();
				ui->AddElement<UI::UIButton>(button);
				continue;
			}

			if (line.find("Text") != std::string::npos)
			{
				ui->AddText(BuildText());
				continue;
			}

			if (line.find("Popup") != std::string::npos)
			{
				ui->AddElement<UI::UIElement>(BuildPopup());
				continue;
			}

			if (line.find("Scrollbox") != std::string::npos)
			{
				ui->AddElement<UI::UIElement>(BuildScrollbox());
				continue;
			}

			if (line.find("Slider") != std::string::npos)
			{
				auto slider = BuildSlider();
				slider->Build();
				ui->AddElement<UI::UISlider>(slider);
				continue;
			}

			if (line.find("Element") != std::string::npos)
			{
				auto element = BuildElement();
				element->Build();
				ui->AddElement<UI::UIElement>(element);
				continue;
			}

			std::getline(m_Stream, line, '<');
		}
		m_Stream.close();
	}
	
	std::unique_ptr<UIElement> UIBuilder::BuildElement()
	{
		auto element = std::make_unique<UIElement>();

		std::string line;
		while (line != "/Element")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

			if (line == "id")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				element->SetID(text);
				continue;
			}

			if (line == "hidden")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				if (text == "true")
				{
					element->Hide();
				}
				continue;
			}

			if (line == "position")
			{
				m_Stream >> element->position.x >> element->position.y;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> element->xSize >> element->ySize;
				continue;
			}

			if (line == "colour")
			{
				m_Stream >> element->colour.r >> element->colour.g >> element->colour.b;
				continue;
			}

			if (line == "alpha")
			{
				m_Stream >> element->colour.a;
				continue;
			}

			if (line == "thickness")
			{
				float thickness;
				m_Stream >> thickness;
				element->ySize = thickness;
				continue;
			}

			if (line == "depth")
			{
				m_Stream >> element->position.z;
				continue;
			}

			if (line == "Text")
			{
				element->AddText(BuildText());
				continue;
			}
		}

		return element;
	}

	std::unique_ptr<UIButton> UIBuilder::BuildButton()
	{
		auto button = std::make_unique<UIButton>();

		float minX = 0.0f, minY = 0.0f, maxX = 0.0f, ySize = 0.0f;
		std::string line;
		while (line != "/Button")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

			if (line == "id")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				button->SetID(text);
				continue;
			}

			if (line == "hidden")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				if (text == "true")
				{
					button->Hide();
				}
				continue;
			}

			if (line == "position")
			{
				m_Stream >> button->position.x >> button->position.y;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> button->xSize >> button->ySize;
				continue;
			}

			if (line == "colour")
			{
				m_Stream >> button->colour.r >> button->colour.g >> button->colour.b;
				continue;
			}

			if (line == "depth")
			{
				m_Stream >> button->position.z;
				continue;
			}

			if (line == "alpha")
			{
				m_Stream >> button->colour.a;
				continue;
			}

			if (line == "persistantalpha")
			{
				m_Stream >> button->m_PersistantAlpha;
				continue;
			}

			if (line == "onMouseDown")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				button->m_MouseDown = StringToEnum(action);
				continue;
			}

			if (line == "onMouseOver")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				button->m_MouseOver = StringToEnum(action);
				continue;
			}

			if (line == "onMouseOut")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				button->m_MouseOut = StringToEnum(action);
				continue;
			}

			if (line == "onMouseUp")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				button->m_MouseUp = StringToEnum(action);
				continue;
			}

			if (line == "Text")
			{
				button->AddText(BuildText());
				continue;
			}

		}

		return button;
	}

	std::unique_ptr<UIDropdown> UIBuilder::BuildDropdown()
	{
		auto dropdown = std::make_unique<UIDropdown>();

		std::string line;
		while (line != "/Dropdown")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');
			
			if (line == "hidden")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				if (text == "true")
				{
					dropdown->Hide();
				}
				continue;
			}

			if (line == "position")
			{
				m_Stream >> dropdown->position.x >> dropdown->position.y;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> dropdown->xSize >> dropdown->ySize;
				continue;
			}

			if (line == "colour")
			{
				m_Stream >> dropdown->colour.r >> dropdown->colour.g >> dropdown->colour.b;
				continue;
			}

			if (line == "Text")
			{
				dropdown->AddText(BuildText());
				continue;
			}

			if (line == "Button")
			{
				dropdown->AddElement(BuildButton());
				continue;
			}

			if (line == "Dropdown")
			{
				dropdown->AddElement(BuildDropdown());
				continue;
			}

			if (line == "Element")
			{
				dropdown->AddElement(BuildElement());
				continue;
			}

		}
		
		return dropdown;
	}

	std::unique_ptr<UIElement> UIBuilder::BuildPopup()
	{
		auto popup = std::make_unique<UIPopup>();

		std::string line;
		while (line != "/Popup")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

			if (line == "id")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				popup->SetID(text);
				continue;
			}

			if (line == "hidden")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				if (text == "true")
				{
					popup->Hide();
				}
				continue;
			}

			if (line == "position")
			{
				m_Stream >> popup->position.x >> popup->position.y;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> popup->xSize >> popup->ySize;
				continue;
			}

			if (line == "colour")
			{
				m_Stream >> popup->colour.r >> popup->colour.g >> popup->colour.b;
				continue;
			}

			if (line == "alpha")
			{
				m_Stream >> popup->colour.a;
				continue;
			}

			if (line == "depth")
			{
				float depth = 0.0f;
				m_Stream >> depth;
				popup->position.z -= depth;
				continue;
			}

			if (line == "Text")
			{
				popup->AddText(BuildText());
				continue;
			}

			if (line.find("Slider") != std::string::npos)
			{
				popup->AddElement(BuildSlider());
				continue;
			}

			if (line.find("Element") != std::string::npos)
			{
				popup->AddElement(BuildElement());
				continue;
			}

			if (line == "Button")
			{
				popup->AddElement(BuildButton());
				continue;
			}

		}

		popup->Build();
		return popup;
	}

	std::unique_ptr<UIElement> UIBuilder::BuildScrollbox()
	{
		auto scrollbox = std::make_unique<UIScrollbox>();

		std::string line;
		while (line != "/Scrollbox")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

			if (line == "id")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				scrollbox->SetID(text);
				continue;
			}

			if (line == "hidden")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				if (text == "true")
				{
					scrollbox->Hide();
				}
				continue;
			}

			if (line == "position")
			{
				m_Stream >> scrollbox->position.x >> scrollbox->position.y;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> scrollbox->xSize >> scrollbox->ySize;
				continue;
			}

			if (line == "colour")
			{
				m_Stream >> scrollbox->colour.r >> scrollbox->colour.g >> scrollbox->colour.b;
				continue;
			}

			if (line == "alpha")
			{
				m_Stream >> scrollbox->colour.a;
				continue;
			}

			if (line == "depth")
			{
				m_Stream >> scrollbox->position.z;
				continue;
			}

			if (line == "Text")
			{
				scrollbox->AddText(BuildText());
				continue;
			}

			if (line.find("Element") != std::string::npos)
			{
				scrollbox->AddElement(BuildElement());
				continue;
			}

			if (line == "Button")
			{
				scrollbox->AddElement(BuildButton());
				continue;
			}

		}

		scrollbox->Build();
		return scrollbox;
	}

	std::unique_ptr<UISlider> UIBuilder::BuildSlider()
	{
		auto slider = std::make_unique<UISlider>();
		
		std::string line;
		while (line != "/Slider")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

			if (line == "hidden")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				if (text == "true")
				{
					slider->Hide();
				}
				continue;
			}

			if (line == "position")
			{
				m_Stream >> slider->position.x >> slider->position.y;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> slider->xSize >> slider->ySize;
				continue;
			}

			if (line == "colour")
			{
				m_Stream >> slider->colour.r >> slider->colour.g >> slider->colour.b;
				continue;
			}

			if (line == "value")
			{
				float value;
				m_Stream >> value;
				slider->SetValue(value);
			}

			if (line == "direction")
			{
				std::string direction;
				std::getline(m_Stream, direction, '<');
				if (direction == "horizontal")
				{
					slider->SetVertical(false);
				}
			}

			/*if (line == "valuerange")
			{
				float min, max;
				m_Stream >> min >> max;
				slider->SetValueRange(min, max);
			}*/

			if (line == "Text")
			{
				slider->AddText(BuildText());
				continue;
			}

			if (line.find("Element") != std::string::npos)
			{
				auto element = BuildElement();
				slider->AddElement(element);
				continue;
			}
		}
		
		return slider;
	}

	std::shared_ptr<UIText> UIBuilder::BuildText()
	{
		auto text = std::make_shared<UIText>();

		std::string line;
		while (line != "/Text")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

			if (line == "hidden")
			{
				std::string hide;
				std::getline(m_Stream, hide, '<');
				if (hide == "true")
				{
					text->Hide();
				}
				continue;
			}

			if (line == "position")
			{
				//TODO: Update to x, y, z
				float x, y;
				m_Stream >> x >> y;
				text->SetPosition(x, y);
				continue;
			}

			if (line == "size")
			{
				float size;
				m_Stream >> size;
				text->SetSize(size);
				continue;
			}

			if (line == "font")
			{
				std::string font;
				std::getline(m_Stream, font, '<');
				text->SetFont(font);
				continue;
			}

			if (line == "key")
			{
				std::string key;
				std::getline(m_Stream, key, '<');
				text->SetKey(key);
				continue;
			}

			if (line == "keynumber")
			{
				unsigned int keyNumber;
				m_Stream >> keyNumber;
				text->SetKeyNumber(keyNumber);
				continue;
			}

			if (line == "colour")
			{
				float r, g, b;
				m_Stream >> r >> g >> b;
				text->SetColour(r, g, b);
				continue;
			}

			if (line == "halign")
			{
				std::string align;
				std::getline(m_Stream, align, '<');
				//TODO: Add Left and Right align
				if (align == "center")
				{
					text->SetCenter();
				}
				continue;
			}

			if (line == "linesize")
			{
				float size;
				m_Stream >> size;
				text->SetLineSize(size);
				continue;
			}

			if (line == "indent")
			{
				float xIn, yIn;
				m_Stream >> xIn >> yIn;
				text->X += xIn / 100.0f;
				text->Y += yIn / 100.0f;
				continue;
			}
		}

		return text;
	}

	ACTION UIBuilder::StringToEnum(const std::string& value)
	{
		if (value == "Menu")		return ACTION::MENU;
		if (value == "Play")		return ACTION::PLAY;
		if (value == "Editor")		return ACTION::EDITOR;
		if (value == "Settings")	return ACTION::SETTINGS;
		if (value == "Exit")		return ACTION::EXIT;
		if (value == "Continue")	return ACTION::CONTINUE;
		if (value == "Load")		return ACTION::LOAD;
		if (value == "Save")		return ACTION::SAVE;
		if (value == "Show")		return ACTION::SHOW;
		if (value == "Hide")		return ACTION::HIDE;
		if (value == "Toggle")		return ACTION::TOGGLE;
		if (value == "AddColour")	return ACTION::ADD_COLOUR;
		if (value == "Undo")		return ACTION::UNDO;
		if (value == "Redo")		return ACTION::REDO;
		if (value == "NextStep")	return ACTION::NEXT_STEP;
		if (value == "PrevStep")	return ACTION::PREV_STEP;

		return ACTION::NONE;
	}

}
