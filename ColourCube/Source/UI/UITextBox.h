#ifndef UI_TEXT_BOX_H
#define UI_TEXT_BOX_H
#include <memory>
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
		std::unique_ptr<UIBackground> m_Background;

		float m_Time;
		float m_PrevTime = 0.0f;

		std::string m_FontName;
		
	public:
		UITextBox(const std::string& key, unsigned int keyNumber, float textSpeed = 2.5f);
		~UITextBox();

		void Update() override;
		bool Continue() override;

		void SetFontName(const std::string& name);

		auto& FontName()		{ return m_FontName; }
		auto& GetHitBox()		{ return m_HitBox; }
		auto& GetBackground()	{ return m_Background; }
	};
}
#endif