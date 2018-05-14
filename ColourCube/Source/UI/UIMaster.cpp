#include "UIMaster.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "Font/FontType.h"
#include "UIText.h"
#include "../Display.h"
#include "UIElement.h"
#include "UITextBox.h"

namespace UI
{
	UIMaster::UIMaster()
		: m_UpdateNeeded(false), m_MousePicker(nullptr)
	{

	}

	UIMaster::~UIMaster()
	{
		
	}

	void UIMaster::Build(const std::string& state)
	{
		std::fstream stream("Resources/Data/" + state + ".xml");
		std::string line;
		while (std::getline(stream, line, ' '))
		{
			if (line.find("text") != std::string::npos)
			{
				BuildText(stream);
				continue;
			}

			if (line.find("element") != std::string::npos)
			{
				BuildElement(stream);
				continue;
			}

			std::getline(stream, line, '<');
		}
		m_UpdateNeeded = true;
		stream.close();
	}

	void UIMaster::AddElement(TYPE type, std::unique_ptr<UIElement>& element)
	{
		m_UpdateNeeded = true;
		m_Elements[type].emplace_back(std::move(element));
	}
	
	std::unique_ptr<UIText>& UIMaster::AddText(const std::string& fontName, const std::string& key, float x, float y)
	{
		m_UpdateNeeded = true;

		if (m_Texts.find(fontName) != m_Texts.end())
		{
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>(key, x, y));
		}
		else
		{
			m_Texts[fontName].first = std::make_unique<Text::FontType>(fontName);
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>(key, x, y));
		}
		return m_Texts[fontName].second.back();
	}

	void UIMaster::AddText(const std::string& fontName, std::unique_ptr<UIText> text)
	{
		m_UpdateNeeded = true;

		if (m_Texts.find(fontName) != m_Texts.end())
		{
			m_Texts[fontName].second.emplace_back(std::move(text));
		}
		else
		{
			m_Texts[fontName].first = std::make_unique<Text::FontType>(fontName);
			m_Texts[fontName].second.emplace_back(std::move(text));
		}
	}

	void UIMaster::AddTextBox(const std::string& fontName, const std::string& key, unsigned int keyNumber)
	{
		std::unique_ptr<UITextBox> textBox = std::make_unique<UITextBox>(key, keyNumber);

		AddElement(TYPE::TEXTBOX, textBox->GetBackground());
		AddText(fontName, std::move(textBox));

		m_UpdateNeeded = true;
	}

	void UIMaster::HandleEvents(std::shared_ptr<Display> display)
	{
		m_Action = ACTION::NONE;

		if (m_MousePicker)
		{
			m_MousePicker->HandleEvents(display);
			if (m_MousePicker->IsToggled())
			{
				m_Action = m_MousePicker->GetAction(m_Elements);
				if (m_Action != ACTION::NONE)
				{
					m_UpdateNeeded = true;
				}
				m_MousePicker->MoveElement(m_Elements[TYPE::SLIDER]);
				if (!m_Elements[TYPE::SLIDER].empty())
				{
					m_Elements[TYPE::COLOUR_CHOOSER].back()->SetColour(
						m_Elements[TYPE::SLIDER][0]->GetValue(),
						m_Elements[TYPE::SLIDER][1]->GetValue(),
						m_Elements[TYPE::SLIDER][2]->GetValue()
					);
				}
			}
			m_MousePicker->HighlightElement(m_Elements[TYPE::BUTTON]);
			m_MousePicker->HighlightElement(m_Elements[TYPE::TEXTBOX]);
		}
	}

	void UIMaster::Update()
	{
		if (m_UpdateNeeded)
		{
			m_UpdateNeeded = false;
			for (auto& font : m_Texts)
			{
				for (auto& text = font.second.second.begin(); text != font.second.second.end();)
				{			
					if (!text->get()->isCreated())
					{
						text->get()->CreateMesh(font.second.first.get());
					}
					if (text->get()->UpdateNeeded())
					{
						text->get()->Update();
						m_UpdateNeeded = true;
					}
					if (text->get()->RemovalNeeded())
					{
						text = font.second.second.erase(text);
					}
					else
					{
						++text;
					}
				}
			}
		}
	}

	void UIMaster::Continue()
	{
		for (auto& text : m_Texts["Arial"].second)
		{
			if (!text->Continue())
			{
				text->Remove();
				m_Elements[TYPE::TEXTBOX].clear();
			}
		}
	}

	void UIMaster::Reveal()
	{
		for (auto& slider : m_Elements[UI::TYPE::SLIDER])
		{
			if (slider->IsHidden())
			{
				slider->SetHidden(false);
			}
		}
		for (auto& background : m_Elements[UI::TYPE::BACKGROUND])
		{
			if (background->IsHidden())
			{
				background->SetHidden(false);
			}
		}
		for (auto& text : m_Texts["Arial"].second)
		{
			if (text->IsHidden())
			{
				text->SetHidden(false);
			}
		}
	}

	void UIMaster::BuildText(std::fstream& stream)
	{
		auto& text = std::make_unique<UIText>();

		std::string line;

		std::string font, key;
		unsigned int keyNumber = 0;
		float x = 0.0f, y = 0.0f, size = 1.0f, r, g, b;
		bool center = false;
		while (line != "/text")
		{
			std::getline(stream, line, '<');
			std::getline(stream, line, '>');

			if (line == "font")
			{
				std::getline(stream, font, '<');
				continue;
			}

			if (line == "key")
			{
				std::getline(stream, key, '<');
				text->SetKey(key);
				continue;
			}

			if (line == "keynumber")
			{
				stream >> keyNumber;
				text->SetKeyNumber(keyNumber);
				continue;
			}

			if (line == "position")
			{
				stream >> x >> y;
				text->SetPosition(x, y);
				continue;
			}

			if (line == "size")
			{
				stream >> size;
				text->SetSize(size);
				continue;
			}

			if (line == "colour")
			{
				stream >> r >> g >> b;
				text->SetColour(r, g, b);
			}

			if (line == "center")
			{
				std::string centered;
				std::getline(stream, centered, '<');
				center = centered == "true" ? true : false;
				text->SetCenter(center);
				continue;
			}
		}
		AddText(font, std::move(text));
	}

	void UIMaster::BuildElement(std::fstream& stream)
	{
		auto& element = std::make_unique<UIElement>();

		float minX = 0.0f, minY = 0.0f, maxX = 0.0f, maxY = 0.0f;
		float r = 1.0f, g = 1.0f, b = 1.0f;
		bool hidden = false;

		std::string line;
		std::getline(stream, line, '\n');
		std::string type;
		if (line.find("type") != std::string::npos)
		{
			auto it = line.find('"');
			while (line[++it] != '"')
				type += line[it];
		}

		while (line != "/element")
		{
			std::getline(stream, line, '<');
			std::getline(stream, line, '>');

			if (line == "hidden")
			{
				std::string text;
				std::getline(stream, text, '<');
				if (text == "true")
				{
					hidden = true;
					element->SetHidden(hidden);
				}
				continue;
			}

			if (line == "position")
			{
				stream >> minX >> minY;
				element->SetMin(minX, minY);
				continue;
			}

			if (line == "size")
			{
				stream >> maxX >> maxY;
				element->SetMax(maxX, maxY);
				continue;
			}

			if (line == "onMouseDown")
			{
				std::string action;
				std::getline(stream, action, '<');
				element->SetAction(action);
				continue;
			}

			if (line == "colour")
			{
				stream >> r >> g >> b;
				element->SetColour(r, g, b);
				continue;
			}

			if (line == "depth")
			{
				float depth;
				stream >> depth;
				element->SetDepth(depth);
				continue;
			}

			if (line == "value")
			{
				float value;
				stream >> value;
				element->SetWidth(maxX)
					->SetValue(value);
			}

			if (line.find("text") != std::string::npos)
			{
				auto& text = std::make_unique<UIText>();
				text->SetPosition(minX, minY)
					->SetHidden(hidden);
				std::string font;
				while (line != "/text")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');

					if (line == "font")
					{
						std::getline(stream, font, '<');
						continue;
					}

					if (line == "key")
					{
						std::string key;
						std::getline(stream, key, '<');
						text->SetKey(key);
						continue;
					}

					if (line == "keynumber")
					{
						unsigned int keyNumber;
						stream >> keyNumber;
						text->SetKeyNumber(keyNumber);
						continue;
					}

					if (line == "size")
					{
						float size;
						stream >> size;
						text->SetSize(size);
						continue;
					}

					if (line == "colour")
					{
						float r, g, b;
						stream >> r >> g >> b;
						text->SetColour(r, g, b);
						continue;
					}

					if (line == "halign")
					{
						std::string align;
						std::getline(stream, align, '<');
						if (align == "center")
						{
							text->SetPosition((minX + (maxX / 2.0f)) - 50.0f, minY)
								->SetCenter(true);
						}
						if (align == "left")
						{
							text->SetPosition(minX - 8.0f, minY);
						}
						continue;
					}
				}

				AddText(font, std::move(text));
			}

			if (line.find("slider") != std::string::npos)
			{
				while (line != "/slider")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');

					if (line == "width")
					{
						float width;
						stream >> width;
						element->SetWidth(maxX);
						element->SetMax(width, maxY);
						continue;
					}

					if (line == "depth")
					{
						float depth;
						stream >> depth;
						element->SetDepth(depth);
						continue;
					}

				}
			}

			if (line.find("background") != std::string::npos)
			{
				auto& background = std::make_unique<UIElement>();
				background->SetMin(minX, minY)
					->SetColour(r, g, b)
					->SetHidden(hidden);
				while (line != "/background")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');

					if (line == "thickness")
					{
						float thickness;
						stream >> thickness;
						background->SetMin(minX, minY + (maxY / 2.0f) - thickness / 2.0f)
							->SetMax(maxX, thickness);
						continue;
					}

					if (line == "depth")
					{
						float depth;
						stream >> depth;
						background->SetDepth(depth);
						continue;
					}

					if (line == "colour")
					{
						float r, g, b;
						stream >> r >> g >> b;
						background->SetColour(r, g, b);
						continue;
					}
				}
				background->Build();
				m_Elements[TYPE::BACKGROUND].emplace_back(std::move(background));
			}

		}

		element->Build();
		if (type == "button")
		{
			m_Elements[TYPE::BUTTON].emplace_back(std::move(element));
		}
		if (type == "background")
		{
			m_Elements[TYPE::BACKGROUND].emplace_back(std::move(element));
		}
		if (type == "colourchooser")
		{
			m_Elements[TYPE::COLOUR_CHOOSER].emplace_back(std::move(element));
		}
		if (type == "slider")
		{
			m_Elements[TYPE::SLIDER].emplace_back(std::move(element));
		}

		if (!m_MousePicker)
		{
			m_MousePicker = std::make_unique<Input::UIMousePicker>();
		}

		m_UpdateNeeded = true;
	}

}
