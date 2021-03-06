#ifndef UI_POPUP_H
#define UI_POPUP_H
#include "UIElement.h"

namespace UI
{
	class UISlider;
	class UIButton;
	class UIDragBar;

	class UIPopup : public UIElement
	{
	public:
		UIPopup() noexcept;
		~UIPopup();

		void Hide(bool hide = true)								override;

		void AddElement(std::shared_ptr<UIElement>& element)	override;
		void AddElement(std::shared_ptr<UISlider>& element);
		void AddElement(std::shared_ptr<UIButton>& element);
		void AddElement(std::shared_ptr<UIDragBar>& element);

		glm::vec4& GetColour()									override;

	protected:
		void AddTraits()										override;

	};
}

#endif