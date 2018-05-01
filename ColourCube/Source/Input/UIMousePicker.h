#ifndef UI_MOUSE_PICKER_H
#define UI_MOUSE_PICKER_H
#include <memory>
#include <vector>
#include <unordered_map>
#include "../UI/UIHitBox.h"

struct Display;
namespace UI { 
	enum class TYPE
	{
		BACKGROUND,
		TEXTBOX,
		BUTTON,
		SLIDER
	};
	class UIBackground; 
}

namespace Input
{
	class UIMousePicker
	{
	private:
		double mouseX, mouseY;
		float m_ToggledTime = 0.0f;
		bool m_Toggled = false;

	public:
		UIMousePicker();
		~UIMousePicker();

		void HandleEvents(std::shared_ptr<Display> display);
		ACTION GetAction(std::unordered_map<UI::TYPE, std::vector<std::unique_ptr<UI::UIHitBox>>>& hitBoxes);
		void Highlight(std::vector<std::unique_ptr<UI::UIBackground>>& backgrounds, std::vector<std::unique_ptr<UI::UIHitBox>>& hitBoxes);
		void MoveSlider(std::vector<std::unique_ptr<UI::UIBackground>>& sliders, std::vector<std::unique_ptr<UI::UIHitBox>>& hitBoxes);

		inline bool IsToggled() const { return m_Toggled; }
	};
}

#endif