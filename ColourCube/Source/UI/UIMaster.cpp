#include "UIMaster.h"
#include "Font/FontType.h"
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

	void UIMaster::AddBackground(UIBackground& background)
	{
		m_Backgrounds.emplace_back(background);
	}
	
	void UIMaster::AddText(const std::string& fontName, const UIText& text)
	{
		m_UpdateNeeded = true;
	
		if (m_Texts.find(fontName) != m_Texts.end())
		{
			m_Texts[fontName].second.emplace_back(text);
		}
		else
		{
			m_Texts[fontName].first = std::make_unique<Text::FontType>(fontName);
			m_Texts[fontName].second.emplace_back(text);
		}

	}

	void UIMaster::AddButton(const std::string& font, UIButton& button)
	{
		AddBackground(button.GetBackground());

		AddText(font, button.GetText());
	}

	void UIMaster::UpdateText()
	{
		if (m_UpdateNeeded)
			m_UpdateNeeded = false;

		for (auto& font : m_Texts)
		{
			for (auto& text : font.second.second)
			{
				text.CreateMesh(font.second.first.get());
			}
		}
	}
}
