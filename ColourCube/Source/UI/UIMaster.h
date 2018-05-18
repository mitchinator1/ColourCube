#ifndef UI_MASTER_H
#define UI_MASTER_H
#include <vector>
#include <unordered_map>
#include <memory>
#include "UIElement.h"
#include "UIText.h"

struct Display;
namespace Text { class FontType; }
namespace Input { class UIMousePicker; }

namespace UI
{
	typedef std::pair<std::unique_ptr<Text::FontType>, std::vector<std::unique_ptr<UIText>>> FontList;

	class UIMaster
	{
	private:
		bool m_UpdateNeeded;
		ACTION m_Action;
		std::unordered_map<TYPE, std::vector<std::unique_ptr<UIElement>>> m_Elements;
		std::unordered_map<std::string, FontList> m_Texts;
		std::unique_ptr<Input::UIMousePicker> m_MousePicker;

	public:
		UIMaster() noexcept;
		~UIMaster();

		void Build(const std::string& state);

		void AddElement(TYPE type, std::unique_ptr<UIElement>& element);
		void AddElement(const std::string& type, std::unique_ptr<UIElement>& element);
		std::unique_ptr<UIText>& AddText(const std::string& fontName, const std::string& key);
		void AddText(const std::string& fontName, std::unique_ptr<UIText> text);

		void HandleEvents(std::shared_ptr<Display> display); 
		void Update();
		void Continue();
		void Reveal(ACTION action);
		void Hide(ACTION action);

		glm::vec3& GetColour();

		inline auto& GetElements()	{ return m_Elements; }
		inline auto& GetTexts()		{ return m_Texts; }
		inline auto GetAction()		{ return m_Action; }

	private:
		TYPE StringToEnum(const std::string& text);
		
	};
}

#endif