#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include "UIElement.h"

namespace UI
{
	class UIText;

	class UIButton : public UIElement
	{
	public:
		UIButton() noexcept;
		~UIButton();

		void Update()											override;

		void AddElement(std::unique_ptr<UIElement>& element)	override;
		void AddElement(std::unique_ptr<UIButton>& element);

		ACTION OnMouseOver()									override;
		ACTION OnMouseOut()										override;

	};
}

#endif