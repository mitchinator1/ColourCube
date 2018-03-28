#include "UIButton.h"
#include <iostream>
namespace UI
{
	//TODO: Fix background width (based on text width or preset width?)
	UIButton::UIButton(Text::GUIText text, glm::vec3 colour)
		: m_Text(text), m_Colour(colour)
		, m_Background(m_Text.GetPosition().x, m_Text.GetPosition().y, m_Text.GetMaxLineSize() / 3.5f, m_Text.GetFontSize() * 0.033f, m_Text.IsCentered())
	{
		
	}

	UIButton::~UIButton()
	{

	}

}