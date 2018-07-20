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

		void Reveal(bool reveal = true)							override;
		void Hide(bool hide = true)								override;

		ACTION OnMouseOver()									override;
		ACTION OnMouseOut()										override;
		ACTION OnMouseUp()										override;

		void AddElement(std::unique_ptr<UIElement>& element)	override;
		void AddElement(std::unique_ptr<UIButton>& element);
		void AddElement(std::unique_ptr<UIDropdown>& element);

	};
}

#endif