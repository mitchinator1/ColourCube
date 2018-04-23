#include "UIMaster.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Font/FontType.h"
#include "UIText.h"
#include "UIBackground.h"
#include "../Input/UIMousePicker.h"
#include "../Display.h"
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

	void UIMaster::AddBackground(float x, float y, float xSize, float ySize, glm::vec3 colour, float alpha)
	{
		m_Backgrounds.emplace_back(std::make_unique<UIBackground>(x, y, xSize, ySize, colour, alpha));
	}

	void UIMaster::AddBackground(std::unique_ptr<UIBackground> background)
	{
		m_Backgrounds.emplace_back(std::move(background));
	}
	
	void UIMaster::AddText(const std::string& fontName, const std::string& text, float size, float x, float y, glm::vec3 colour)
	{
		m_UpdateNeeded = true;

		if (m_Texts.find(fontName) != m_Texts.end())
		{
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>(text, size, x, y));
		}
		else
		{
			m_Texts[fontName].first = std::make_unique<Text::FontType>(fontName);
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>(text, size, x, y));
		}
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

	void UIMaster::AddButton(const std::string& fontName, const std::string& key, ACTION action, float x, float y, float xSize, float ySize, glm::vec3 colour)
	{
		if (!m_MousePicker)
		{
			m_MousePicker = std::make_unique<Input::UIMousePicker>();
		}

		AddBackground(x, y, xSize, ySize, colour);
		AddHitBox(action, x, y, x + xSize, y + ySize);
		AddText(fontName, LoadText(key), 3.0f, x - 40.0f, y, colour);
	}

	void UIMaster::AddTextBox(const std::string& fontName, const std::string& key)
	{
		std::unique_ptr<UITextBox> textBox = std::make_unique<UITextBox>(LoadText(key));

		AddHitBox(textBox->GetHitBox());
		AddBackground(std::move(textBox->GetBackground()));
		AddText(fontName, std::move(textBox));
	}

	void UIMaster::HandleEvents(std::shared_ptr<Display> display)
	{
		m_Action = ACTION::NONE;

		if (m_MousePicker->GetMouseInput(display))
		{
			m_Action = m_MousePicker->GetAction(m_HitBoxes);
			if ((int)m_Action)
				m_UpdateNeeded = true;
		}
	}

	void UIMaster::Update()
	{
		if (m_UpdateNeeded)
		{
			m_UpdateNeeded = false;

			for (auto& font : m_Texts)
			{
				for (auto& text : font.second.second)
				{					
					if (!text->isCreated())
					{
						text->CreateMesh(font.second.first.get());
					}
					if (text->UpdateNeeded())
					{
						text->Update();
						m_UpdateNeeded = true;
					}
				}
			}
		}
	}

	void UIMaster::Continue()
	{
		auto& textBox = m_Texts["Arial"].second.back();

		if (textBox->UpdateNeeded())
		{
			textBox->Continue();
		}
		else
		{
			textBox->SetText(LoadText("help" + std::to_string(++textBox->GetKey())));
		}
	}

	void UIMaster::AddHitBox(ACTION action, float xMin, float yMin, float xMax, float yMax)
	{
		m_HitBoxes.emplace_back(action, xMin, yMin, xMax, yMax);
	}

	void UIMaster::AddHitBox(UIHitBox& hitbox)
	{
		m_HitBoxes.emplace_back(hitbox);
	}

	const std::string UIMaster::LoadText(const std::string& key)
	{
		std::ifstream stream("Resources/Text/Menu.text");
		std::string line;
		while (std::getline(stream, line))
		{
			if (line.find(key) != std::string::npos)
			{
				std::istringstream part(line);
				std::getline(part, line, '"');
				stream >> line;
				std::getline(part, line, '"');
				break;
			}
		}

		return line;
	}

}
