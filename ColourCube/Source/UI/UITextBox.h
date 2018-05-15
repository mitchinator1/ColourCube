#ifndef UI_TEXT_BOX_H
#define UI_TEXT_BOX_H
#include <memory>
#include "UIText.h"

namespace UI
{
	class UITextBox : public UIText
	{
	private: 
		float m_TextSpeed;
		unsigned int m_CurrentCharCount;
		
	public:
		UITextBox();
		~UITextBox();

		void Update() override;
		bool Continue() override;
	};
}
#endif