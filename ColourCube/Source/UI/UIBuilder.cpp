#include "UIBuilder.h"
#include <iostream>
#include "UIMaster.h"
#include "UITextBox.h"
#include "UIDropdown.h"
#include "UIButton.h"
#include "UIText.h"

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
				//TODO: Where elements are added
				ui->AddElement(TYPE::BUTTON, BuildDropdown());
				continue;
			}

			if (line.find("Button") != std::string::npos)
			{
				ui->AddElement(TYPE::BUTTON, BuildButton());
				continue;
			}

			if (line.find("Text") != std::string::npos)
			{
				ui->AddText(BuildText());
				continue;
			}

			if (line.find("Element") != std::string::npos)
			{
				ui->AddElement(TYPE::BACKGROUND, BuildElement("Element"));
				continue;
			}

			std::getline(m_Stream, line, '<');
		}
		m_Stream.close();
	}

	/*
		std::string type;
		if (line.find("type") != std::string::npos)
		{
			auto it = line.find('"');
			while (line[++it] != '"')
				type += line[it];
		}

		if (line == "value")
		{
			float value;
			m_Stream >> value;
			element->SetWidth(maxX)
				->SetValue(value);
			continue;
		}

		if (line == "valuerange")
		{
			float min, max;
			m_Stream >> min >> max;
			element->SetValueRange(min, max);
			continue;
		}

	if (line.find("slider") != std::string::npos)
	{
		while (line != "/slider")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

			if (line == "width")
			{
				float width;
				m_Stream >> width;
				element->SetWidth(maxX);
					//->SetMax(width, maxY);
				continue;
			}

		}
	}

	if (line.find("background") != std::string::npos)
	{
		background->SetColour(r, g, b)->SetHidden(hidden);
		
		if (line == "thickness")
		{
			float thickness;
			m_Stream >> thickness;
			//background->SetMin(minX, minY + (maxY / 2.0f) - thickness / 2.0f)
			//	->SetMax(maxX, thickness);
			continue;
		}

	*/

	std::unique_ptr<UIButton> UIBuilder::BuildButton()
	{
		auto button = std::make_unique<UIButton>();

		float minX = 0.0f, minY = 0.0f, maxX = 0.0f, maxY = 0.0f;
		std::string line;
		while (line != "/Button")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

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

			if (line.find("Text") != std::string::npos)
			{
				auto text = BuildText();
				if (text->IsCentered())
				{
					text->SetPosition((button->minX + (button->maxX / 2.0f)) - 50.0f, button->minY)
						->SetCenter(true);
				}
				text->SetHidden(button->IsHidden());
				button->AddText(text);
				continue;
			}
			
		}

		button->Build();

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

			if (line.find("Text") != std::string::npos)
			{
				auto text = BuildText();
				if (text->IsCentered())
				{
					text->SetPosition((dropdown->minX + (dropdown->maxX / 2.0f)) - 50.0f, dropdown->minY)
						->SetCenter(true);
				}
				if (dropdown->IsHidden())
				{
					text->SetHidden(true);
				}
				dropdown->AddText(text);
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

		}
		
		dropdown->Build();

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
					text->SetHidden(true);
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
					text->SetCenter(true);
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
				//Fix indent
				text->SetPosition(text->GetPosition().x + xIn, text->GetPosition().y + yIn);
				continue;
			}
		}

		return text;
	}

	std::unique_ptr<UIElement> UIBuilder::BuildElement(const std::string& type)
	{
		auto element = std::make_unique<UIElement>();

		std::string line;
		while (line != ("/" + type))
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

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

		element->Build();
		return element;
	}

}
