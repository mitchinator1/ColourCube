#ifndef UI_TEXT_BOX_H
#define UI_TEXT_BOX_H
#include "UIText.h"
#include "UIHitBox.h"
#include "UIBackground.h"

namespace UI
{
	class UITextBox : public UIText
	{
	private: 
		float m_TextSpeed;
		unsigned int m_CurrentCharCount;

		UIHitBox m_HitBox;

		float m_Time;
		float m_PrevTime = 0.0f;
		
	public:
		UITextBox(const std::string& text, float textSpeed = 2.5f);
		~UITextBox();

		void Update() override;
	};
}
#endif