#ifndef UI_MASTER_H
#define UI_MASTER_H
#include <vector>
#include <unordered_map>
#include <memory>
#include "GLM/glm.hpp"
#include "UIHitBox.h"

struct Display;
namespace Text { class FontType; }
namespace Input { class UIMousePicker; }
namespace UI
{
	class UIText;
	class UIBackground;
	typedef std::pair<std::unique_ptr<Text::FontType>, std::vector<std::unique_ptr<UIText>>> FontList;
	
	class UIMaster
	{
	private:
		bool m_UpdateNeeded;
		ACTION m_Action;
		std::vector<std::unique_ptr<UIBackground>> m_Backgrounds;
		std::unordered_map<std::string, FontList> m_Texts;
		std::vector<UIHitBox> m_HitBoxes;
		std::unique_ptr<Input::UIMousePicker> m_MousePicker;

	public:
		UIMaster();
		~UIMaster();

		void AddBackground(float x, float y, float xSize, float ySize, glm::vec3 colour, float alpha = 1.0f);
		void AddBackground(std::unique_ptr<UIBackground> background);
		void AddText(const std::string& fontName, const std::string& key, unsigned int keyNumber, float size, float x, float y, glm::vec3 colour);
		void AddText(const std::string& fontName, std::unique_ptr<UIText> text);
		void AddButton(const std::string& fontName, const std::string& key, unsigned int keyNumber, ACTION action, float x, float y, float xSize, float ySize, glm::vec3 colour);
		void AddTextBox(const std::string& fontName, const std::string& key, unsigned int keyNumber = 0);

		void HandleEvents(std::shared_ptr<Display> display); 
		void Update();
		void Continue();

		inline auto& GetBackgrounds()	{ return m_Backgrounds; }
		inline auto& GetTexts()			{ return m_Texts; }
		inline auto GetAction()			{ return m_Action; }

	private:
		void AddHitBox(ACTION action, float xMin, float yMin, float xMax, float yMax);
		void AddHitBox(UIHitBox& hitbox);
	};
}

#endif