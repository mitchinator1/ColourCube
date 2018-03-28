#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include "../Mesh/Font/GUIText.h"
#include "UIBackground.h"

namespace UI
{
	class UIButton
	{
	private:
		Text::GUIText m_Text;

		glm::vec3 m_Colour;
		float m_Size;

		UIBackground m_Background;

	public:
		UIButton(Text::GUIText text, glm::vec3 colour);
		~UIButton();

		Text::GUIText* GetText() { return &m_Text; }
		UIBackground& GetBackground() { return m_Background; }
	};
}

#endif