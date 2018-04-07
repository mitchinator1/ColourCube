#include "FontType.h"
#include "GL/glew.h"
#include <iostream>

#include "TextMeshCreator.h"
#include "../../Mesh/Texture.h"

namespace Text
{
	FontType::FontType(const std::string& fontFile)
		: m_FontName(fontFile), m_TextureAtlas(0)
		, m_Loader(std::make_unique<TextMeshCreator>("Resources/Font/" + fontFile + ".fnt"))
		, m_Texture(std::make_unique<Texture>("Resources/Font/" + fontFile + ".png"))
	{

	}

	FontType::~FontType()
	{

	}

	void FontType::Bind() const
	{
		m_Texture->Bind();
	}

	void FontType::Unbind() const
	{
		m_Texture->Unbind();
	}

	std::vector<float> FontType::LoadText(UI::UIText& text) const
	{
		return m_Loader->CreateVertexData(text);
	}

	bool FontType::operator==(const FontType& rhs) const
	{
		return (m_FontName == rhs.m_FontName);
	}

	bool FontType::operator==(const std::string& name) const
	{
		return (m_FontName == name);
	}

	bool FontType::operator==(const char* name) const
	{
		return (m_FontName == name);
	}
}