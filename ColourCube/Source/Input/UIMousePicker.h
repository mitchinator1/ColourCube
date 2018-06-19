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
	typedef std::vector<std::unique_ptr<UI::UIElement>> ElementList;

	class UIMousePicker : Mouse2D
	{
	public:
		UIMousePicker(std::shared_ptr<Display>& display);
		~UIMousePicker();

		void HandleEvents(UI::UIMaster* ui);

	private:
		UI::ACTION GetMouseOver(ElementList& elements);
		UI::ACTION GetMouseDown(UI::UIMaster* ui);
		UI::ACTION GetMouseUp(UI::UIMaster* ui);

	};
}

#endif