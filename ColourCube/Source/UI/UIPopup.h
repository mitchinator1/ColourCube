#ifndef UI_POPUP_H
#define UI_POPUP_H
#include "UIElement.h"

namespace UI
{
	class UISlider;

	class UIPopup : public UIElement
	{
	public:
		UIPopup();
		~UIPopup();

		void Update()											override;
		void Reveal(bool reveal = true)							override;
		void Hide(bool hide = true)								override;

		void AddElement(std::unique_ptr<UIElement>& element)	override;
		void AddElement(std::unique_ptr<UISlider>& element);

		bool InRange(float x, float y);

		void Build()											override;
	};
}

#endif