#ifndef UI_SCROLLBOX_H
#define UI_SCROLLBOX_H
#include "UIElement.h"

namespace UI
{
	class UISlider;
	class UIButton;
	class UIDragBar;

	class UIScrollbox : public UIElement
	{
	public:
		UIScrollbox();
		~UIScrollbox();

		void AddElement(std::unique_ptr<UIElement>& element)	override;
		void AddElement(std::unique_ptr<UISlider>& element);
		void AddElement(std::unique_ptr<UIButton>& element);
		void AddElement(std::unique_ptr<UIDragBar>& element);

	protected:
		void AddTraits()										override;
	};
}

#endif