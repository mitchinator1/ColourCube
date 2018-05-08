#ifndef UI_TEXT_BOX_H
#define UI_TEXT_BOX_H
#include <memory>
#include "UIText.h"
#include "UIElement.h"

namespace UI
{
	class UITextBox : public UIText
	{
	private: 
		float m_TextSpeed;
		unsigned int m_CurrentCharCount;

		std::unique_ptr<UIElement> m_Background;
		
	public:
		UITextBox(const std::string& key, unsigned int keyNumber, float textSpeed = 2.5f);
		~UITextBox();

		void Update() override;
		bool Continue() override;

		auto& GetBackground()	{ return m_Background; }
	};
}
#endif