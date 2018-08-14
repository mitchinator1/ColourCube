#ifndef UI_POPUP_H
#define UI_POPUP_H
#include "UIElement.h"

namespace UI
{
	class UISlider;
	class UIButton;

	class UIPopup : public UIElement
	{
	public:
		UIPopup() noexcept;
		~UIPopup();

		bool InRange(float x, float y)							override;

		void Hide(bool hide = true)								override;

		void AddElement(std::unique_ptr<UIElement>& element)	override;
		void AddElement(std::unique_ptr<UISlider>& element);
		void AddElement(std::unique_ptr<UIButton>& element);

		glm::vec4& GetColour()									override;
	};
}

#endif