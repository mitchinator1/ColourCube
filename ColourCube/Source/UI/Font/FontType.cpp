#include "FontType.h"
#include "TextMeshCreator.h"
#include "../../Mesh/Texture.h"

namespace Text
{
	FontType::FontType(const std::string& fontFile, double width, double height) noexcept
		: m_FontName(fontFile)
		, m_Loader(std::make_unique<TextMeshCreator>("Resources/Font/" + fontFile + ".fnt", width, height))
		, m_Texture(std::make_shared<Texture>("Resources/Font/" + fontFile + ".png"))
	{

	}

	FontType::~FontType()
	{

	}

	std::vector<float> FontType::LoadText(UI::UIText& text) const
	{
		return m_Loader->CreateVertexData(text);
	}

	std::shared_ptr<Texture>& FontType::GetTexture()
	{
		return m_Texture;
	}

}