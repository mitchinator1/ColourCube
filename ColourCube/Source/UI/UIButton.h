#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include "UIText.h"
#include "UIBackground.h"

namespace UI
{
	class UIButton
	{
	private:
		UIText m_Text;

		glm::vec3 m_Colour;
		float m_Size;

		UIBackground m_Background;

	public:
		UIButton(UIText text, glm::vec3 colour = { 0.0f, 0.0f, 0.0f });
		~UIButton();

		inline UIText& GetText() { return m_Text; }
		inline UIBackground& GetBackground() { return m_Background; }
	};
}

#endif