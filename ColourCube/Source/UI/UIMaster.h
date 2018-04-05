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
	typedef std::pair<std::unique_ptr<Text::FontType>, std::vector<UIText>> FontList;

	class UIMaster
	{
	private:
		bool m_UpdateNeeded;
		std::vector<UIBackground> m_Backgrounds;
		std::unordered_map<std::string, FontList> m_Texts;

	public:
		UIMaster();
		~UIMaster();

		void AddBackground(UIBackground& background);
		void AddText(const std::string& fontName, const UIText& text);
		void AddButton(const std::string& font, UIButton& button);

		void UpdateText();

		inline std::vector<UIBackground>& GetBackgrounds() { return m_Backgrounds; }
		inline std::unordered_map<std::string, FontList>& GetTexts() { return m_Texts; }
	};
}

#endif