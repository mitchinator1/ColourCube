#ifndef UI_MASTER_H
#define UI_MASTER_H
#include <vector>
#include <unordered_map>
#include <memory>
#include "Element/UIElement.h"
#include "Element/UIText.h"

struct Display;
namespace Text { class FontType; }
namespace Input { class UIMousePicker; }

namespace UI
{
	class UIDropdown;
	class UIButton;
	class UISlider;
	typedef std::pair<std::unique_ptr<Text::FontType>, std::vector<std::shared_ptr<UIText>>> FontList;

	class UIMaster
	{
	private:
		bool m_UpdateNeeded;
		ACTION m_Action;
		std::string m_ID = "";
		std::vector<std::unique_ptr<UIElement>> m_Elements;
		std::unordered_map<std::string, FontList> m_Texts;
		std::unique_ptr<Input::UIMousePicker> m_Mouse;
		std::shared_ptr<Display> m_Display;

	public:
		UIMaster(std::shared_ptr<Display>& display);
		~UIMaster();

		void Build(const std::string& state);

		void AddElement(std::unique_ptr<UIElement>& element);
		void AddElement(std::unique_ptr<UIButton>& element);
		void AddElement(std::unique_ptr<UIDropdown>& element);
		void AddElement(std::unique_ptr<UISlider>& element);
		std::shared_ptr<UIText>& AddText(const std::string& fontName, const std::string& key);
		void AddText(std::shared_ptr<UIText>& text);

		void HandleEvents(std::shared_ptr<Display> display); 
		void Update();
		void Continue();
		void Reveal(const std::string& id);

		glm::vec3& GetColour();

		void SetAction(ACTION action);

		const std::string& GetID();

		inline auto& GetElements()	{ return m_Elements; }
		inline auto& GetTexts()		{ return m_Texts; }
		inline auto GetAction()		{ return m_Action; }

	private:
		void GrabTexts(std::unique_ptr<UIElement>& element);
		
	};
}

#endif