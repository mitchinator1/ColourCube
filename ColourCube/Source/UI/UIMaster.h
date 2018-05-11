#ifndef UI_MASTER_H
#define UI_MASTER_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "GLM/glm.hpp"
#include "UIElement.h"
#include "Font/FontType.h"
#include "UIText.h"
#include "../Input/UIMousePicker.h"

struct Display;
namespace Text { class FontType; }

namespace UI
{
	class UIElement;
	class UIText;
	typedef std::pair<std::unique_ptr<Text::FontType>, std::vector<std::unique_ptr<UIText>>> FontList;
	
	class UIMaster
	{
	private:
		bool m_UpdateNeeded;
		ACTION m_Action;
		std::unordered_map<TYPE, std::vector<std::unique_ptr<UIElement>>> m_Elements;
		std::unordered_map<std::string, FontList> m_Texts;
		std::unordered_map<TYPE, std::vector<std::unique_ptr<UIElement>>> m_HitBoxes;
		std::unique_ptr<Input::UIMousePicker> m_MousePicker;

	public:
		UIMaster();
		~UIMaster();

		void Build(const std::string& state);

		void AddElement(TYPE type, std::unique_ptr<UIElement>& element);
		std::unique_ptr<UIText>& AddText(const std::string& fontName, const std::string& key, float x, float y);
		void AddText(const std::string& fontName, std::unique_ptr<UIText> text);
		void AddTextBox(const std::string& fontName, const std::string& key, unsigned int keyNumber = 0);

		void HandleEvents(std::shared_ptr<Display> display); 
		void Update();
		void Continue();

		inline auto& GetElements()	{ return m_Elements; }
		inline auto& GetTexts()		{ return m_Texts; }
		inline auto GetAction()		{ return m_Action; }

	private:
		void BuildText(std::fstream& stream);
		void BuildBackground(std::fstream& stream);
		void BuildButton(std::fstream& stream);
		void BuildSlider(std::fstream& stream);
		
	};
}

#endif