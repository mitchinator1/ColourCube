#include "RendererFont.h"
#include <iostream>

namespace Renderer
{
	RendererFont::RendererFont()
		: m_Shader(std::make_unique<Shader::ShaderFont>())
	{
		//TODO: pair shared_ptr<Font>, GUIText
	}

	RendererFont::~RendererFont()
	{

	}

	void RendererFont::Prepare()
	{
		m_Shader->Bind();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
	}

	void RendererFont::Render(Text::GUIText* text)
	{
		//Prepare();
		

		//for (auto& itext : m_Text)
		//{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, text->GetFont().GetTextureAtlas());
			RenderText(*text);
		//}

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

		//EndRendering();
	}

	void RendererFont::EndRendering()
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		m_Shader->Unbind();
	}

	void RendererFont::RenderText(Text::GUIText& text)
	{
		text.Bind();

		m_Shader->LoadColour(text.GetColour());
		m_Shader->LoadTranslation(text.GetPosition());

		glDrawElements(GL_TRIANGLES, text.GetCount(), GL_UNSIGNED_INT, nullptr);

		text.Unbind();
	}

}