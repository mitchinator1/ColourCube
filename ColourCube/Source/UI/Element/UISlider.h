#ifndef UI_SLIDER_H
#define UI_SLIDER_H
#include "UIElement.h"

namespace UI
{
	class UIButton;
	class UIDragBar;

	class UISlider : public UIElement
	{
	private:
		float m_Value = 0.0f;
		float* m_ValuePtr = nullptr;
		bool m_IsVertical = true;

	public:
		UISlider() noexcept;
		~UISlider();

		void AddElement(std::unique_ptr<UIElement>& element)	override;
		void AddElement(std::unique_ptr<UIDragBar>& element);

		void Update()					override;
		bool InRange(float x, float y)	override;

		ACTION OnMouseDown()			override;

		UISlider* SetValue(float value);
		UISlider* SetValuePointer(float* value);
		UISlider* SetVertical(bool isVertical = true);

	private:
		void UpdateValue(float value);

	protected:
		void AddTraits()				override;

	};
}
#endif