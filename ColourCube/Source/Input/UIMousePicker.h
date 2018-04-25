#ifndef UI_MOUSE_PICKER_H
#define UI_MOUSE_PICKER_H
#include <memory>
#include <vector>
#include "../UI/UIHitBox.h"

struct Display;

namespace Input
{
	class UIMousePicker
	{
	private:
		float m_Toggled;
		double mouseX, mouseY;

	public:
		UIMousePicker();
		~UIMousePicker();

		bool GetMouseInput(std::shared_ptr<Display> display);
		ACTION GetAction(std::vector<std::unique_ptr<UI::UIHitBox>>& hitBoxes);
	};
}

#endif