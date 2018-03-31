#ifndef UI_MASTER_H
#define UI_MASTER_H
#include "UIBackground.h"
#include "UIText.h"
#include "UIButton.h"
#include "../Mesh/Mesh.h"

#include <vector>
#include <unordered_map>

namespace UI
{
	class UIMaster
	{
	private:
		std::vector<UIBackground> m_Backgrounds;
		Mesh* m_BackgroundMesh;
		Mesh* m_TextMesh;

		std::unordered_map<std::shared_ptr<Text::FontType>, std::vector<UIText>> m_Texts;

	public:
		UIMaster();
		~UIMaster();

		void AddElement(UIButton& button);
		void AddBackground(UIBackground& background);
		void AddText(std::shared_ptr<Text::FontType> font, UIText& text);
		void AddButton(UIButton& button);

		void CalculateMesh();

		void Bind();
		void Unbind();

		inline std::unordered_map<std::shared_ptr<Text::FontType>, std::vector<UIText>>& GetTexts() { return m_Texts; }
		inline unsigned int GetCount() { return m_BackgroundMesh->GetCount(); }
	};
}

#endif