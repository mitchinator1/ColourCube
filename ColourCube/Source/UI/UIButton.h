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
		bool InRange(float x, float y)							override;

		void AddElement(std::unique_ptr<UIElement>& element)	override;
		void AddText(std::shared_ptr<UIText>& text)				override;

		ACTION OnMouseOver()									override;
		ACTION OnMouseOut()										override;
		ACTION OnMouseDown()									override;
	};
}

#endif