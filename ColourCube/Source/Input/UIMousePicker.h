#ifndef UI_MOUSE_PICKER_H
#define UI_MOUSE_PICKER_H
#include <memory>
#include <vector>

struct Display;
namespace UI { struct UIHitBox; }

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
		unsigned int GetID(std::vector<UI::UIHitBox>& hitBoxes);
	};
}

#endif