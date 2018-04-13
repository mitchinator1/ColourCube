#include "UIMaster.h"
#include <iostream>
#include "Font/FontType.h"
#include "UIText.h"
#include "UIBackground.h"
#include "../Input/UIMousePicker.h"
#include "../Display.h"

namespace UI
{
	UIMaster::UIMaster()
		: m_UpdateNeeded(false), m_MousePicker(nullptr)
	{

	}

	UIMaster::~UIMaster()
	{
		
	}

	void UIMaster::AddBackground(float x, float y, float xSize, float ySize, glm::vec3 colour)
	{
		m_Backgrounds.emplace_back(std::make_unique<UIBackground>(x, y, xSize, ySize, colour));
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

	void UIMaster::AddButton(const std::string& fontName, const std::string& text, ACTION action, float x, float y, float xSize, float ySize, glm::vec3 colour)
	{
		if (!m_MousePicker)
		{
			m_MousePicker = std::make_unique<Input::UIMousePicker>();
		}

		AddBackground(x, y, xSize, ySize, colour);
		AddHitBox(action, x, y, x + xSize, y + ySize);
		AddText(fontName, text, 3.0f, x - 40.0f, y, colour);
	}

	void UIMaster::AddTextBox(const std::string& fontName, const std::string& text)
	{
		std::unique_ptr<UIText> textString = std::make_unique<UIText>(text, 2.0f, 5.0f, 60.0f, 90.0f, false);
		AddText(fontName, std::move(textString));
	}

	void UIMaster::UpdateText()
	{
		if (m_UpdateNeeded)
		{
			m_UpdateNeeded = false;

			for (auto& font : m_Texts)
			{
				for (auto& text : font.second.second)
				{
					text->CreateMesh(font.second.first.get());
				}
			}
		}
	}

	void UIMaster::HandleEvents(std::shared_ptr<Display> display)
	{
		m_Action = ACTION::NONE;

		if (m_MousePicker->GetMouseInput(display))
		{
			m_Action = m_MousePicker->GetAction(m_HitBoxes);
			m_UpdateNeeded = true;
		}
	}

	void UIMaster::AddHitBox(ACTION action, float xMin, float yMin, float xMax, float yMax)
	{
		xMin = (xMin / 100.0f) * 2.0f - 1.0f;
		yMin = (yMin / 100.0f) * 2.0f - 1.0f;
		xMax = (xMax / 100.0f) * 2.0f - 1.0f;
		yMax = (yMax / 100.0f) * 2.0f - 1.0f;

		m_HitBoxes.emplace_back(action, xMin, yMin, xMax, yMax);
	}
}