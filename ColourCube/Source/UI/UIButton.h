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
		UIBackground m_Background;

		glm::vec2 m_Position;
		glm::vec3 m_Colour;
		float m_Size;

	public:
		UIButton(Text::GUIText text, glm::vec2 position, glm::vec3 colour, float size);
		~UIButton();

		Text::GUIText* GetText();
	};
}

#endif