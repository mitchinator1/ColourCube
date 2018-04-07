#ifndef UI_MASTER_H
#define UI_MASTER_H
#include "UIBackground.h"
#include "UIText.h"
#include "UIButton.h"
#include "../Mesh/Mesh.h"
#include "Font/FontType.h"

#include <vector>
#include <unordered_map>

namespace UI
{
	typedef std::pair<std::unique_ptr<Text::FontType>, std::vector<std::unique_ptr<UIText>>> FontList;

	class UIMaster
	{
	private:
		bool m_UpdateNeeded;
		std::vector<std::unique_ptr<UIBackground>> m_Backgrounds;
		std::unordered_map<std::string, FontList> m_Texts;

	public:
		UIMaster();
		~UIMaster();

		void AddBackground(std::unique_ptr<UIBackground> background);
		void AddText(const std::string& fontName, std::unique_ptr<UIText> text);
		void AddButton(const std::string& fontName, const std::string& text, float x, float y, float xSize, float ySize, glm::vec3 colour);

		void UpdateText();

		inline std::vector<std::unique_ptr<UIBackground>>& GetBackgrounds() { return m_Backgrounds; }
		inline std::unordered_map<std::string, FontList>& GetTexts() { return m_Texts; }
	};
}

#endif