#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include <memory>
#include "UIText.h"
//#include "UIBackground.h"

namespace UI
{
	class UIButton
	{
	private:
		//std::unique_ptr<UIText> m_Text;

		float m_X, m_Y, m_XSize, m_YSize;
		glm::vec3 m_Colour;
		float m_Size;

		//UIBackground m_Background;

	public:
		UIButton(float x, float y, float xSize, float ySize, glm::vec3 colour);
		~UIButton();

		//inline std::unique_ptr<UIText> GetText() { return m_Text; }
		//inline UIBackground& GetBackground() { return m_Background; }
	};
}

#endif