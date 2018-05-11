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

		//YODO: Abstract build methods. "value = read<float>(1, stream);"

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
				BuildButton(stream);

				continue;
			}

			if (line.find("slider") != std::string::npos)
			{
				BuildSlider(stream);

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
		auto& background = std::make_unique<UIElement>();

		std::string line;

		while (line != "/background")
		{
			std::getline(stream, line, '<');
			std::getline(stream, line, '>');

			if (line == "position")
			{
				float x, y;
				stream >> x >> y;
				background->SetMin(x, y);
				continue;
			}

			if (line == "size")
			{
				float x, y;
				stream >> x >> y;
				background->SetMax(x, y);
				continue;
			}

			if (line == "colour")
			{
				float r, g, b;
				stream >> r >> g >> b;
				background->SetColour(r, g, b);
				continue;
			}

			if (line == "depth")
			{
				float depth;
				stream >> depth;
				background->SetDepth(depth);
				continue;
			}
		}
		background->Build();
		AddElement(TYPE::BACKGROUND, background);
	}

	void UIMaster::BuildButton(std::fstream& stream)
	{
		auto& text = std::make_unique<UIText>();
		auto& button = std::make_unique<UIElement>();
		auto& hitbox = std::make_unique<UIElement>();

		float minX = 0.0f, minY = 0.0f, maxX = 0.0f, maxY = 0.0f;

		std::string line;
		while (line != "/button")
		{
			std::getline(stream, line, '<');
			std::getline(stream, line, '>');

			if (line == "position")
			{
				stream >> minX >> minY;
				text->SetPosition(minX, minY);
				button->SetMin(minX, minY);
				hitbox->SetMin(minX, minY);
				continue;
			}

			if (line == "size")
			{
				stream >> maxX >> maxY;
				button->SetMax(maxX, maxY);
				hitbox->SetMax(maxX, maxY);
				continue;
			}

			if (line == "onMouseDown")
			{
				std::string action;
				std::getline(stream, action, '<');
				button->SetAction(action);
				continue;
			}

			if (line.find("text") != std::string::npos)
			{
				std::string font;
				while(line != "/text")
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
						continue;
					}
				}

				AddText(font, std::move(text));
			}

			if (line.find("element") != std::string::npos)
			{
				while (line != "/element")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');

					if (line == "colour")
					{
						float r, g, b;
						stream >> r >> g >> b;
						button->SetColour(r, g, b);
						continue;
					}

					if (line == "depth")
					{
						float depth;
						stream >> depth;
						button->SetDepth(depth);
						continue;
					}

				}
				button->Build();
				m_Elements[TYPE::BUTTON].emplace_back(std::move(button));
				m_HitBoxes[TYPE::BUTTON].emplace_back(std::move(hitbox));
			}

		}

		if (!m_MousePicker)
		{
			m_MousePicker = std::make_unique<Input::UIMousePicker>();
		}

		m_UpdateNeeded = true;
	}

	void UIMaster::BuildSlider(std::fstream& stream)
	{
		auto& text = std::make_unique<UIText>();
		auto& slider = std::make_unique<UIElement>();
		auto& hitbox = std::make_unique<UIElement>();
		auto& background = std::make_unique<UIElement>();
		
		float minX = 0.0f, minY = 0.0f, maxX = 0.0f, maxY = 0.0f;
		float width = 0.0f, height = 0.0f;
		float value = 0.0f;
		
		std::string line;
		while (line != "/slider")
		{
			std::getline(stream, line, '<');
			std::getline(stream, line, '>');

			if (line == "position")
			{
				stream >> minX >> minY;
				text->SetPosition(minX, minY);
				slider->SetMin(minX, minY);
				hitbox->SetMin(minX, minY);
				continue;
			}

			if (line == "size")
			{
				stream >> width >> height;
				hitbox->SetMax(width, height);
				continue;
			}

			if (line == "action")
			{
				std::string action;
				stream >> action;
				slider->SetAction(action);
				continue;
			}

			if (line == "value")
			{
				stream >> value;
				continue;
			}

			if (line.find("text") != std::string::npos)
			{
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
				continue;
			}

			if (line.find("element") != std::string::npos)
			{
				while (line != "/element")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');
					
					if (line == "width")
					{
						float width;
						stream >> width;
						slider->SetMax(width, height);
						continue;
					}

					if (line == "colour")
					{
						float r, g, b;
						stream >> r >> g >> b;
						slider->SetColour(r, g, b);
						continue;
					}

					if (line == "depth")
					{
						float depth;
						stream >> depth;
						slider->SetDepth(depth);
						continue;
					}

				}
				slider->SetWidth(width)
					->SetValue(value)
					->Build();
				AddElement(TYPE::SLIDER, std::move(slider));
				m_HitBoxes[TYPE::SLIDER].emplace_back(std::move(hitbox));
			}

			if (line.find("background") != std::string::npos)
			{
				while (line != "/background")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');

					if (line == "thickness")
					{
						float y;
						stream >> y;
						background->SetMin(minX, minY + (height / 2.0f) - y / 2.0f);
						background->SetMax(width, y);
						continue;
					}

					if (line == "colour")
					{
						float r, g, b;
						stream >> r >> g >> b;
						background->SetColour(r, g, b);
						continue;
					}

					if (line == "depth")
					{
						float depth;
						stream >> depth;
						background->SetDepth(depth);
						continue;
					}
				}
				background->Build();
				AddElement(TYPE::BACKGROUND, background);
			}
		}
	}

}
