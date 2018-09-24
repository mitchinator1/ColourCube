#ifndef UI_TEXT_ENTRY_H
#define UI_TEXT_ENTRY_H
#include "UIElement.h"

namespace UI
{
	class UITextEntry : public UIElement
	{
	private:
		bool m_Activated = false;

	public:
		UITextEntry();
		~UITextEntry();

		ACTION OnMouseUp();
	};

}

#endif