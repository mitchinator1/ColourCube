#include "RendererFont.h"
#include <iostream>

namespace Renderer
{
	RendererFont::RendererFont()
		: m_Shader(std::make_unique<Shader::ShaderFont>()), m_FontType(std::make_shared<Text::FontType>("Arial"))
	{
		//TODO: pair shared_ptr<Font>, GUIText
		m_Text.emplace_back(new Text::GUIText("Text that expands onto multiple lines!", 4.0f, m_FontType, { 0.01f, 0.0f }, 1.0f, false));
	}

	RendererFont::~RendererFont()
	{
		for (auto& text : m_Text)
			delete text;
	}

	void RendererFont::Render()
	{
		Prepare();
		

		for (auto& text : m_Text)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_FontType->GetTextureAtlas());
			RenderText(*text);
		}

		//	for (const auto& element : texts)
		//	{
		//		element.first.GetTextureAtlas();
		//		glActiveTexture(GL_TEXTURE0);
		//		glBindTexture(GL_TEXTURE_2D, element.first.GetTextureAtlas());
		//		for (auto& text : texts[element.first])
		//		{
		//			RenderText(text);
		//		}
		//	}

		EndRendering();
	}

	void RendererFont::Prepare()
	{
		m_Shader->Bind();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
	}

	void RendererFont::RenderText(Text::GUIText& text)
	{
		text.Bind();

		m_Shader->LoadColour(text.GetColour());
		m_Shader->LoadTranslation(text.GetPosition());

		glDrawElements(GL_TRIANGLES, text.GetVertexCount(), GL_UNSIGNED_INT, nullptr);

		text.Unbind();
	}

	void RendererFont::EndRendering()
	{
		m_Shader->Unbind();
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}
}