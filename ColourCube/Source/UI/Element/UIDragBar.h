#ifndef UI_DRAG_BAR_H
#define UI_DRAG_BAR_H
#include "UIElement.h"

namespace UI
{
	class UIDragBar : public UIElement
	{
	private:
		UIElement* m_Parent;

	public:
		UIDragBar();
		~UIDragBar();

		bool InRange(float x, float y)	override;

		void SetValuePointer(UIElement* element);

	};
}

#endif