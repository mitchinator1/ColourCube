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

		while (std::getline(stream, line, '<'))
		{
			std::getline(stream, line, '>');

			if (line.find("text") != std::string::npos)
			{
				BuildText(stream);
				continue;
			}

			if (line.find("background") != std::string::npos)
			{
				BuildBackground(stream);
				continue;
			}

			if (line.find("button") != std::string::npos)
			{
				while (line != "/button")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');

					if (line.find("text") != std::string::npos)
					{
						BuildText(stream);
						continue;
					}

					if (line.find("element") != std::string::npos)
					{
						BuildElement(stream, TYPE::BUTTON);
						continue;
					}
					
				}
				continue;
			}

			if (line.find("slider") != std::string::npos)
			{
				while (line != "/slider")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');

					if (line.find("text") != std::string::npos)
					{
						BuildText(stream);
						continue;
					}

					if (line.find("element") != std::string::npos)
					{
						BuildElement(stream, TYPE::SLIDER);
						continue;
					}

					if (line.find("background") != std::string::npos)
					{
						BuildBackground(stream);
						continue;
					}
				}
				continue;
			}
		}
		m_UpdateNeeded = true;
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
		m_UpdateNeeded = true;

		AddElement(TYPE::TEXTBOX, textBox->GetBackground());
		AddText(fontName, std::move(textBox));
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
				m_MousePicker->MoveSlider(m_Elements[TYPE::SLIDER], m_HitBoxes[TYPE::SLIDER]);
			}
			m_MousePicker->Highlight(m_Elements[TYPE::BUTTON], m_HitBoxes[TYPE::BUTTON]);
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

	void UIMaster::BuildBackground(std::fstream& stream)
	{
		std::string line;

		float minX, minY, maxX, maxY;
		float r, g, b;
		float depth = 0.0f;
		while (line != "/background")
		{
			std::getline(stream, line, '<');
			std::getline(stream, line, '>');

			if (line == "position")
			{
				stream >> minX >> minY;
				continue;
			}

			if (line == "size")
			{
				stream >> maxX >> maxY;
				continue;
			}

			if (line == "colour")
			{
				stream >> r >> g >> b;
				continue;
			}

			if (line == "depth")
			{
				stream >> depth;
				continue;
			}
		}
		AddElement<TYPE::BACKGROUND>(minX, minY, maxX, maxY)
			->SetColour(r, g, b)
			->SetDepth(depth)
			->Build();
	}

	void UIMaster::BuildElement(std::fstream& stream, TYPE type)
	{
		std::string line;

		float minX, minY, maxX, maxY;
		float r, g, b;
		float depth = 0.0f;
		ACTION action = ACTION::NONE;
		while (line != "/element")
		{
			std::getline(stream, line, '<');
			std::getline(stream, line, '>');

			if (line == "action")
			{
				std::string text;
				std::getline(stream, text, '<');

				action = TextToEnum(text);
				continue;
			}

			if (line == "position")
			{
				stream >> minX >> minY;
				continue;
			}

			if (line == "size")
			{
				stream >> maxX >> maxY;
				continue;
			}

			if (line == "colour")
			{
				stream >> r >> g >> b;
				continue;
			}

			if (line == "depth")
			{
				stream >> depth;
				continue;
			}
		}
		if (type == TYPE::SLIDER)
		{
			AddElement<TYPE::SLIDER>(minX, minY, maxX, maxY)
				->SetColour(r, g, b)
				->SetDepth(depth)
				->SetAction(action)
				->Build();
		}
		if (type == TYPE::BUTTON)
		{
			AddElement<TYPE::BUTTON>(minX, minY, maxX, maxY)
				->SetColour(r, g, b)
				->SetAction(action)
				->Build();
		}
	}

	ACTION UIMaster::TextToEnum(const std::string& text)
	{
		ACTION action = ACTION::NONE;

		if (text == "Menu")
			return ACTION::MENU;
		if (text == "Play")
			return ACTION::PLAY;
		if (text == "Editor")
			return ACTION::EDITOR;
		if (text == "Settings")
			return ACTION::SETTINGS;
		if (text == "Exit")
			return ACTION::EXIT;
		if (text == "Load")
			return ACTION::LOAD;
		if (text == "Save")
			return ACTION::SAVE;
		if (text == "Toggle")
			return ACTION::TOGGLE;
		if (text == "Colour")
			return ACTION::TOGGLE;

		return action;
	}

}
