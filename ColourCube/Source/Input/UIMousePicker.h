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

		void HandleEvents(std::shared_ptr<Display> display);
		UI::ACTION GetMouseOver(std::unordered_map<UI::TYPE, ElementList>& elements);
		UI::ACTION GetMouseDown(std::unordered_map<UI::TYPE, ElementList>& elements);
		void HighlightElement(ElementList& elements);
		void MoveElement(ElementList& sliders);

		inline bool IsToggled() const { return m_Toggled; }
		inline bool IsHeld()	const { return m_Held; }

	private:
		bool BoxInRange(float minX, float minY, float maxX, float maxY);
	};
}

#endif