#ifndef UI_MOUSE_PICKER_H
#define UI_MOUSE_PICKER_H
#include <memory>
#include <vector>
#include <unordered_map>
#include "Mouse2D.h"

namespace UI {
	enum class ACTION;
	class UIElement;
	class UIMaster;
}

namespace Input
{
	typedef std::vector<std::shared_ptr<UI::UIElement>> ElementList;

	class UIMousePicker : Mouse2D
	{
	public:
		UIMousePicker(std::shared_ptr<Display>& display);
		~UIMousePicker();

		bool HandleEvents(UI::UIMaster* ui);

	private:
		bool CheckMouseOver(UI::UIMaster* ui);
		UI::ACTION CheckMouseOver(ElementList& elements);
		void CheckMouseDown(UI::UIMaster* ui);
		void CheckMouseUp(UI::UIMaster* ui);

	};
}

#endif