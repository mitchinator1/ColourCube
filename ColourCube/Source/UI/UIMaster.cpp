#include "UIMaster.h"
#include "Font/FontType.h"
#include "UIText.h"
#include "UIBackground.h"
#include <iostream>

namespace UI
{
	UIMaster::UIMaster()
		: m_UpdateNeeded(false)
	{

	}

	UIMaster::~UIMaster()
	{
		
	}

	void UIMaster::AddBackground(std::unique_ptr<UIBackground> background)
	{
		m_Backgrounds.emplace_back(std::move(background));
	}
	
	//TODO: AddText(const std::string& text, float x, float y, float xSize, float ySize, glm::vec3 colour)

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

	void UIMaster::AddButton(const std::string& fontName, const std::string& text, float x, float y, float xSize, float ySize, glm::vec3 colour)
	{
		AddBackground(std::make_unique<UIBackground>(x, y, xSize, ySize, colour));

		AddText(fontName, std::make_unique<UIText>(text, 3.0f, x - 40.0f, y));
	}

	void UIMaster::UpdateText()
	{
		if (m_UpdateNeeded)
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
