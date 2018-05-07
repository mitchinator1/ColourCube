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

		template<TYPE>
		std::unique_ptr<UIElement>& AddElement(float x, float y, float xSize, float ySize)
		{
			static_assert(false);
		}

		template<>
		std::unique_ptr<UIElement>& AddElement<TYPE::BACKGROUND>(float x, float y, float xSize, float ySize)
		{
			m_UpdateNeeded = true;
			m_Elements[TYPE::BACKGROUND].emplace_back(std::make_unique<UIElement>(x, y, xSize, ySize));
			return m_Elements[TYPE::BACKGROUND].back();
		}

		template<>
		std::unique_ptr<UIElement>& AddElement<TYPE::SLIDER>(float x, float y, float xSize, float ySize)
		{
			if (!m_MousePicker)
			{
				m_MousePicker = std::make_unique<Input::UIMousePicker>();
			}

			std::unique_ptr<UIElement> slider = std::make_unique<UIElement>(x, y, xSize, ySize);
			m_Elements[TYPE::SLIDER].emplace_back(std::move(slider));

			std::unique_ptr<UIElement> hitbox= std::make_unique<UIElement>(x, y, xSize, ySize);
			hitbox->Build();
			m_HitBoxes[TYPE::SLIDER].emplace_back(std::move(hitbox));

			return m_Elements[TYPE::SLIDER].back();
		}

		template<>
		std::unique_ptr<UIElement>& AddElement<TYPE::BUTTON>(float x, float y, float xSize, float ySize)
		{
			if (!m_MousePicker)
			{
				m_MousePicker = std::make_unique<Input::UIMousePicker>();
			}

			m_UpdateNeeded = true;
			m_Elements[TYPE::BUTTON].emplace_back(std::make_unique<UIElement>(x, y, xSize, ySize));
			m_HitBoxes[TYPE::BUTTON].emplace_back(std::make_unique<UIElement>(x, y, xSize, ySize));
			return m_Elements[TYPE::BUTTON].back();
		}

	private:
		void BuildText(std::fstream& stream);
		void BuildBackground(std::fstream& stream);
		void BuildElement(std::fstream& stream, TYPE type);

		ACTION TextToEnum(const std::string& text);

	};
}

#endif