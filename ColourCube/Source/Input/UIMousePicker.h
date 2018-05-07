#ifndef UI_MOUSE_PICKER_H
#define UI_MOUSE_PICKER_H
#include <memory>
#include <vector>
#include <unordered_map>
//#include "../UI/UIHitBox.h"

struct Display;
namespace UI { 
	enum class TYPE;
	enum class ACTION;
	class UIElement;
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
		UI::ACTION GetAction(std::unordered_map<UI::TYPE, std::vector<std::unique_ptr<UI::UIElement>>>& elements);
		void Highlight(std::vector<std::unique_ptr<UI::UIElement>>& buttons, std::vector<std::unique_ptr<UI::UIElement>>& elements);
		void MoveSlider(std::vector<std::unique_ptr<UI::UIElement>>& sliders, std::vector<std::unique_ptr<UI::UIElement>>& elements);

		inline bool IsToggled() const { return m_Toggled; }
	};
}

#endif