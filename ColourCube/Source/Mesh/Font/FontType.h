#pragma once
#include <string>
#include "TextMeshCreator.h"

class Text::GUIText;

namespace Text
{
	class FontType {
	private:
		unsigned int m_TextureAtlas;
		TextMeshCreator* m_Loader;

	public:
		FontType(const std::string& fontFile = "Arial");
		~FontType();

		unsigned int GetTextureAtlas() const;
		TextMeshData LoadText(GUIText& text);

	private:
		void LoadTextureAtlas(const std::string& fontFile);
	};
}