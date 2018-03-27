#include "UIButton.h"

namespace UI
{
	UIButton::UIButton(Text::GUIText text, glm::vec2 position, glm::vec3 colour, float size)
		: m_Text(text), m_Background(position, size), m_Position(position), m_Colour(colour), m_Size(size)
	{

	}

	UIButton::~UIButton()
	{

	}

	Text::GUIText* UIButton::GetText()
	{
		return &m_Text;
	}

}