#include "UIMaster.h"
#include <iostream>
#include "Font/FontType.h"
#include "UIText.h"
#include "../Display.h"
#include "UIBackground.h"
#include "UITextBox.h"
#include "UIHitBox.h"

namespace UI
{
	UIMaster::UIMaster()
		: m_UpdateNeeded(false), m_MousePicker(nullptr)
	{

	}

	UIMaster::~UIMaster()
	{
		
	}

	void UIMaster::AddBackground(TYPE type, float x, float y, float xSize, float ySize, glm::vec3 colour, float alpha)
	{
		m_UpdateNeeded = true;
		m_Backgrounds[type].emplace_back(std::make_unique<UIBackground>(x, y, xSize, ySize, colour, alpha));
	}

	void UIMaster::AddBackground(TYPE type, std::unique_ptr<UIBackground> background)
	{
		m_UpdateNeeded = true;
		m_Backgrounds[type].emplace_back(std::move(background));
	}
	
	void UIMaster::AddText(const std::string& fontName, const std::string& key, unsigned int keyNumber, float size, float x, float y, glm::vec3 colour)
	{
		m_UpdateNeeded = true;

		if (m_Texts.find(fontName) != m_Texts.end())
		{
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>(key, keyNumber, size, x, y));
			m_Texts[fontName].second.back()->SetColour(colour.r, colour.g, colour.b);
		}
		else
		{
			m_Texts[fontName].first = std::make_unique<Text::FontType>(fontName);
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>(key, keyNumber, size, x, y));
			m_Texts[fontName].second.back()->SetColour(colour.r, colour.g, colour.b);
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

	void UIMaster::AddButton(const std::string& fontName, const std::string& key, unsigned int keyNumber, ACTION action, float x, float y, float xSize, float ySize, glm::vec3 colour)
	{
		if (!m_MousePicker)
		{
			m_MousePicker = std::make_unique<Input::UIMousePicker>();
		}

		m_UpdateNeeded = true;

		AddBackground(TYPE::BUTTON, x, y, xSize, ySize, colour - 0.2f);
		AddHitBox(TYPE::BUTTON, action, x, y, x + xSize, y + ySize);
		AddText(fontName, key, keyNumber, 3.0f, x - 40.0f, y, colour);
	}

	void UIMaster::AddTextBox(const std::string& fontName, const std::string& key, unsigned int keyNumber)
	{
		std::unique_ptr<UITextBox> textBox = std::make_unique<UITextBox>(key, keyNumber);

		m_UpdateNeeded = true;

		AddHitBox(TYPE::TEXTBOX, std::move(textBox->GetHitBox()));
		AddBackground(TYPE::TEXTBOX, std::move(textBox->GetBackground()));
		AddText(fontName, std::move(textBox));
	}

	void UIMaster::AddTimedText(const std::string& fontName, const std::string& key, unsigned int keyNumber, float time)
	{
		std::unique_ptr<UIText> text = std::make_unique<UIText>(key, keyNumber, 3.0f, 0.0f, 40.0f);
		text->SetTime(time);

		AddText(fontName, std::move(text));
	}

	void UIMaster::AddSlider(float x, float y, float width)
	{
		AddBackground(TYPE::SLIDER, x, y, 1.0f, 5.0f, { 1.0f, 1.0f, 0.8f });
		AddBackground(TYPE::BUTTON, x, y + 2.5f, width, 0.5f, { 1.0f, 1.0f, 1.0f });
		AddHitBox(TYPE::SLIDER, ACTION::NONE, x, y, x + width, y + 5.0f);
	}

	void UIMaster::HandleEvents(std::shared_ptr<Display> display)
	{
		m_Action = ACTION::NONE;

		m_MousePicker->HandleEvents(display);
		if (m_MousePicker->IsToggled())
		{
			m_Action = m_MousePicker->GetAction(m_HitBoxes);
			if (m_Action != ACTION::NONE)
			{
				m_UpdateNeeded = true;
			}
			m_MousePicker->MoveSlider(m_Backgrounds[TYPE::SLIDER], m_HitBoxes[TYPE::SLIDER]);
		}
		m_MousePicker->Highlight(m_Backgrounds[TYPE::BUTTON], m_HitBoxes[TYPE::BUTTON]);
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
				m_HitBoxes[TYPE::TEXTBOX].pop_back();
				m_Backgrounds[TYPE::TEXTBOX].clear();
			}
		}
	}

	void UIMaster::AddHitBox(TYPE type, ACTION action, float xMin, float yMin, float xMax, float yMax)
	{
		m_HitBoxes[type].emplace_back(std::make_unique<UIHitBox>(action, xMin, yMin, xMax, yMax));
	}

	void UIMaster::AddHitBox(TYPE type, std::unique_ptr<UIHitBox> hitbox)
	{
		m_HitBoxes[type].emplace_back(std::move(hitbox));
	}

}
