#ifndef UI_SLIDER_H
#define UI_SLIDER_H
#include "UIElement.h"

namespace UI
{
	class UIButton;
	class UISlider : public UIElement
	{
	private:
		float m_Value = 0.0f;
		float* m_ValuePtr = nullptr;

	public:
		UISlider() noexcept;
		~UISlider();

		void Update()					override;
		bool InRange(float x, float y)	override;

		ACTION OnMouseDown()			override;

		UISlider* SetValue(float value);
		UISlider* SetValuePointer(float* value);

		void Build()					override;

	private:
		void UpdateValue(float value);

	};
}
#endif