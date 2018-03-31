#include "FontType.h"
#include "GL/glew.h"
#include <iostream>

#include "TextMeshCreator.h"

namespace Text
{
	FontType::FontType(const std::string& fontFile)
		: m_FontName(fontFile), m_TextureAtlas(0)
		, m_Loader(new TextMeshCreator("Resources/Font/" + fontFile + ".fnt"))
		, m_Texture("Resources/Font/" + fontFile + ".png")
	{

	}

	FontType::~FontType()
	{
		delete m_Loader;
	}

	void FontType::Bind()
	{
		m_Texture.Bind();
	}

	void FontType::Unbind()
	{
		m_Texture.Unbind();
	}

	std::vector<float> FontType::LoadText(UI::UIText& text)
	{
		return m_Loader->CreateVertexData(text);
	}

	bool FontType::operator==(const FontType& rhs)
	{
		return (m_FontName == rhs.m_FontName);
	}
}