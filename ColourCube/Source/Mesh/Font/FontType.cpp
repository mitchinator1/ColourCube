#include "FontType.h"
#include "GL/glew.h"
#include <iostream>

namespace Text
{
	FontType::FontType(const std::string& fontFile)
		: m_TextureAtlas(0), m_Loader(new TextMeshCreator("Resources/Font/" + fontFile + ".fnt"))
		, m_Texture("Resources/Font/" + fontFile + ".png")
	{
		//LoadTextureAtlas(fontFile);
	}

	FontType::~FontType()
	{
		delete m_Loader;
	}

	unsigned int FontType::GetTextureAtlas() const
	{
		return m_Texture.GetTexture();
	}

	std::vector<float> FontType::LoadText(GUIText& text)
	{
		return m_Loader->CreateVertexData(text);
	}
}