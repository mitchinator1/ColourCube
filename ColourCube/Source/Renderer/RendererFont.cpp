#include "RendererFont.h"

namespace Renderer
{
	RendererFont::RendererFont()
		: m_Shader(new Shader::ShaderFont())
	{

	}

	RendererFont::~RendererFont()
	{
		delete m_Shader;
	}

	void RendererFont::Render(std::unordered_map<FontType, std::vector<GUIText>> texts)
	{
		Prepare();
		for (FontType& font : texts.keySet()) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, font.getTextureAtlas());
			for (GUIText& text : texts[font]) {
				RenderText(text);
			}
		}
		EndRendering();
	}

	void RendererFont::Prepare()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		m_Shader->Bind();
	}

	void RendererFont::RenderText(GUIText& text)
	{
		glBindVertexArray(text.GetMesh());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		m_Shader->LoadColour(text.GetColour());
		m_Shader->LoadTranslation(text.GetPosition());
		glDrawArrays(GL_TRIANGLES, 0, text.GetVertexCount());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}

	void RendererFont::EndRendering()
	{
		m_Shader->Unbind();
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}
}