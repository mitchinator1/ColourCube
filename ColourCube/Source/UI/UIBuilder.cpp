#include "UIBuilder.h"
#include <iostream>
#include "UIMaster.h"
#include "Element/UITextBox.h"
#include "Element/UIDropdown.h"
#include "Element/UIButton.h"
#include "Element/UISlider.h"
#include "Element/UIPopup.h"
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
				ui->AddElement(dropdown);
				continue;
			}

			if (line.find("Button") != std::string::npos)
			{
				auto button = BuildButton();
				button->Build();
				ui->AddElement(button);
				continue;
			}

			if (line.find("Text") != std::string::npos)
			{
				ui->AddText(BuildText());
				continue;
			}

			if (line.find("Popup") != std::string::npos)
			{
				ui->AddElement(BuildPopup());
				continue;
			}

			if (line.find("Slider") != std::string::npos)
			{
				auto slider = BuildSlider();
				slider->Build();
				ui->AddElement(slider);
				continue;
			}

			if (line.find("Element") != std::string::npos)
			{
				auto element = BuildElement();
				element->Build();
				ui->AddElement(element);
				continue;
			}

			std::getline(m_Stream, line, '<');
		}
		m_Stream.close();
	}
	
	std::unique_ptr<UIButton> UIBuilder::BuildButton()
	{
		auto button = std::make_unique<UIButton>();

		float minX = 0.0f, minY = 0.0f, maxX = 0.0f, maxY = 0.0f;
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
				m_Stream >> button->minX >> button->minY;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> button->maxX >> button->maxY;
				continue;
			}

			if (line == "colour")
			{
				float r, g, b;
				m_Stream >> r >> g >> b;
				button->SetColour(r, g, b);
				continue;
			}

			if (line == "depth")
			{
				float depth;
				m_Stream >> depth;
				button->SetDepth(depth);
				continue;
			}

			if (line == "alpha")
			{
				float alpha;
				m_Stream >> alpha;
				button->SetAlpha(alpha);
				continue;
			}

			if (line == "persistantalpha")
			{
				float alpha;
				m_Stream >> alpha;
				button->SetPersistantAlpha(alpha);
				continue;
			}

			if (line == "onMouseDown")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				button->SetMouseDown(action);
				continue;
			}

			if (line == "onMouseOver")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				button->SetMouseOver(action);
				continue;
			}

			if (line == "onMouseOut")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				button->SetMouseOut(action);
				continue;
			}

			if (line == "onMouseUp")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				button->SetMouseUp(action);
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

		float minX = 0.0f, minY = 0.0f, maxX = 0.0f, maxY = 0.0f;
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
				m_Stream >> dropdown->minX >> dropdown->minY;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> dropdown->maxX >> dropdown->maxY;
				continue;
			}

			if (line == "colour")
			{
				float r, g, b;
				m_Stream >> r >> g >> b;
				dropdown->SetColour(r, g, b);
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
				text->SetPosition(xIn * 100.0f, yIn * 100.0f);
				continue;
			}
		}

		return text;
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
				m_Stream >> popup->minX >> popup->minY;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> popup->maxX >> popup->maxY;
				continue;
			}

			if (line == "colour")
			{
				float r, g, b;
				m_Stream >> r >> g >> b;
				popup->SetColour(r, g, b);
				continue;
			}

			if (line == "alpha")
			{
				float alpha;
				m_Stream >> alpha;
				popup->SetAlpha(alpha);
				continue;
			}

			if (line == "depth")
			{
				float depth;
				m_Stream >> depth;
				popup->SetDepth(depth);
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
				m_Stream >> slider->minX >> slider->minY;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> slider->maxX >> slider->maxY;
				continue;
			}

			if (line == "colour")
			{
				float r, g, b;
				m_Stream >> r >> g >> b;
				slider->SetColour(r, g, b);
				continue;
			}

			if (line == "value")
			{
				float value;
				m_Stream >> value;
				slider->SetValue(value);
			}

			if (line == "valuerange")
			{
				float min, max;
				m_Stream >> min >> max;
				slider->SetValueRange(min, max);
			}

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

		slider->Update();

		return slider;
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
				m_Stream >> element->minX >> element->minY;
				continue;
			}

			if (line == "size")
			{
				m_Stream >> element->maxX >> element->maxY;
				continue;
			}

			if (line == "colour")
			{
				float r, g, b;
				m_Stream >> r >> g >> b;
				element->SetColour(r, g, b);
				continue;
			}

			if (line == "alpha")
			{
				float alpha;
				m_Stream >> alpha;
				element->SetAlpha(alpha);
				continue;
			}

			if (line == "thickness")
			{
				float thickness;
				m_Stream >> thickness;
				element->maxY = thickness;
				continue;
			}

			if (line == "depth")
			{
				float depth;
				m_Stream >> depth;
				element->SetDepth(depth);
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

}
