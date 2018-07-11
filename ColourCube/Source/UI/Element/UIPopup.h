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
		UIPopup();
		~UIPopup();

		void Update()											override;
		bool InRange(float x, float y)							override;
		void Reveal(bool reveal = true)							override;
		void Hide(bool hide = true)								override;

		ACTION OnMouseOut()										override;
		ACTION OnMouseDown()									override;
		ACTION OnMouseUp()										override;

		void AddElement(std::unique_ptr<UIElement>& element)	override;
		void AddElement(std::unique_ptr<UISlider>& element);
		void AddElement(std::unique_ptr<UIButton>& element);

		void Build()											override;
		glm::vec4& GetColour()									override;

		bool IsMouseDown()										override;
		std::string& GetID()									override;
	};
}

#endif