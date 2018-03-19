#include "FontType.h"

namespace Text
{
	FontType::FontType(int textureAtlas, const std::string& fontFile)
		: m_TextureAtlas(textureAtlas), m_Loader(fontFile)
	{

	}

	int FontType::GetTextureAtlas() const
	{
		return m_TextureAtlas;
	}

	TextMeshData& FontType::LoadText(GUIText& text)
	{
		return m_Loader.CreateTextMesh(text);
	}
}