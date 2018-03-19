#pragma once
#include <string>
#include "TextMeshCreator.h"

namespace Text
{
	class FontType {
	private:
		int m_TextureAtlas;
		TextMeshCreator m_Loader;

	public:
		FontType(int textureAtlas, const std::string& fontFile);

		int GetTextureAtlas() const;
		TextMeshData& LoadText(GUIText& text);
	};
}