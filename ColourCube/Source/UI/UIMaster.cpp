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

		while (std::getline(stream, line))
		{
			if (line.find("<text>") != std::string::npos)
			{
				auto& text = std::make_unique<UIText>();

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

			if (line.find("<button>") != std::string::npos)
			{
				while (line != "/button")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');

					if (line.find("text") != std::string::npos)
					{
						auto& text = std::make_unique<UIText>();

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

					if (line.find("element") != std::string::npos)
					{
						float minX, minY, maxX, maxY;
						float r, g, b;
						ACTION action = ACTION::NONE;
						while (line != "/element")
						{
							std::getline(stream, line, '<');
							std::getline(stream, line, '>');

							if (line == "action")
							{
								std::string actionWord;
								std::getline(stream, actionWord, '<');
								if (actionWord == "Menu")
									action = ACTION::MENU;
								if (actionWord == "Play")
									action = ACTION::PLAY;
								if (actionWord == "Editor")
									action = ACTION::EDITOR;
								if (actionWord == "Settings")
									action = ACTION::SETTINGS;
								if (actionWord == "Exit")
									action = ACTION::EXIT;
								if (actionWord == "Load")
									action = ACTION::LOAD;
								if (actionWord == "Save")
									action = ACTION::SAVE;
								if (actionWord == "Toggle")
									action = ACTION::TOGGLE;
								if (actionWord == "Colour")
									action = ACTION::TOGGLE;

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
						}
						AddElement<TYPE::BUTTON>(minX, minY, maxX, maxY)
							->SetAction(action)
							->SetColour(r, g, b)
							->Build();
					}
					
				}
			}

			if (line.find("<background>") != std::string::npos)
			{
				std::getline(stream, line, '<');
				std::getline(stream, line, '>');

				if (line.find("element") != std::string::npos)
				{
					float minX, minY, maxX, maxY;
					float r, g, b;
					while (line != "/element")
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
					}
					AddElement<TYPE::BACKGROUND>(minX, minY, maxX, maxY)
						->SetColour(r, g, b)
						->Build();
				}
			}

			if (line.find("<slider>") != std::string::npos)
			{
				while (line != "/slider")
				{
					std::getline(stream, line, '<');
					std::getline(stream, line, '>');

					if (line.find("element") != std::string::npos)
					{
						float minX, minY, maxX, maxY;
						float r, g, b;
						while (line != "/element")
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
						}
						AddElement<TYPE::SLIDER>(minX, minY, maxX, maxY)
							->SetColour(r, g, b)
							->SetDepth(-0.9f)
							->Build();
					}

					if (line.find("background") != std::string::npos)
					{
						float minX, minY, maxX, maxY;
						float r, g, b;
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
						}
						AddElement<TYPE::BACKGROUND>(minX, minY, maxX, maxY)
							->SetColour(r, g, b)
							->SetDepth(-0.1f)
							->Build();
					}

					if (line.find("text") != std::string::npos)
					{
						auto& text = std::make_unique<UIText>();

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
				}
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

}
