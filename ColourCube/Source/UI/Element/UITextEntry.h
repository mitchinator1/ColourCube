#ifndef UI_TEXT_ENTRY_H
#define UI_TEXT_ENTRY_H
#include "UIElement.h"

namespace UI
{
	class UITextEntry : public UIElement
	{
	public:
		UITextEntry();
		~UITextEntry();
		
		ACTION OnMouseUp();
	};

}

#endif