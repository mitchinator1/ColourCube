#pragma once
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
		glm::vec2 m_Size;

	public:
		UIButton(Text::GUIText text, glm::vec2 position, glm::vec3 colour, glm::vec2 size);
		~UIButton();

		Text::GUIText* GetText();
		Mesh* GetMesh();
	};
}