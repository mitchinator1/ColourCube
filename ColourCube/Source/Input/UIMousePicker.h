#ifndef UI_MOUSE_PICKER_H
#define UI_MOUSE_PICKER_H
#include <memory>
#include <vector>
#include <unordered_map>

struct Display;
namespace UI { 
	enum class TYPE;
	enum class ACTION;
	class UIElement;
	class UIMaster;
}

namespace Input
{
	typedef std::vector<std::unique_ptr<UI::UIElement>> ElementList;

	class UIMousePicker
	{
	private:
		double mouseX = 0.0, mouseY = 0.0;
		bool m_Toggled = false;
		bool m_Held = false;
		float m_ToggledTime = 0.0f;
		const float DELAY = 0.2f;

	public:
		UIMousePicker() noexcept;
		~UIMousePicker();

		void HandleEvents(std::shared_ptr<Display> display, UI::UIMaster* ui);
		UI::ACTION GetMouseOver(ElementList& elements);
		UI::ACTION GetMouseDown(UI::UIMaster* ui);
		UI::ACTION GetMouseUp(ElementList& elements);

		inline bool IsToggled() const { return m_Toggled; }
		inline bool IsHeld()	const { return m_Held; }

	};
}

#endif