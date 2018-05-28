#ifndef UI_DROPDOWN_H
#define UI_DROPDOWN_H
#include "UIElement.h"

namespace UI
{
	class UIButton;
	class UIDropdown : public UIElement
	{		
	public:
		UIDropdown() noexcept;
		~UIDropdown();

		void Update()											override;
		bool InRange(float x, float y)							override;
		void Reveal(bool reveal = true)							override;
		void Hide(bool hide = true)								override;

		void AddElement(std::unique_ptr<UIElement>& element)	override;
		void AddElement(std::unique_ptr<UIButton>& element);
		void AddElement(std::unique_ptr<UIDropdown>& element);
		void AddText(std::shared_ptr<UIText>& text)				override;

		ACTION OnMouseOver()									override;
		ACTION OnMouseOut()										override;
		ACTION OnMouseDown()									override;
	};
}

#endif