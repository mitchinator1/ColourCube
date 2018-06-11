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
		float m_ValueMin = 0.0f;
		float m_ValueMax = 1.0f;

	public:
		UISlider() noexcept;
		~UISlider();

		void Update()					override;
		bool InRange(float x, float y)	override;

		ACTION OnMouseDown()			override;
		ACTION OnMouseUp()				override;

		UISlider* SetValue(float value);
		UISlider* SetValuePointer(float* value);
		UISlider* SetValueRange(float min, float max);

		void Build()					override;

	private:
		void UpdateValue(float value);
	};
}
#endif