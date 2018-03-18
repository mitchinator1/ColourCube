#pragma once
//#include "GLFW/glfw3.h"
#include "GL/glew.h"
#include "../Mesh/Font/FontType.h"
#include "../Shader/ShaderFont.h"

class FontRenderer {
private:
	Shader::ShaderFont* m_Shader;

public:
	FontRenderer()
		: m_Shader(new Shader::ShaderFont())
	{

	}

	void Render(Map<FontType, std::vector<GUIText>> texts)
	{
		Prepare();
		for (FontType& font : texts.keySet()) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, font.getTextureAtlas());
			for (GUIText& text : texts.get(font)) {
				RenderText(text);
			}
		}
		EndRendering();
	}

	void cleanUp()
	{
		m_Shader->CleanUp();
	}

private:
	void Prepare()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		m_Shader->Start();
	}

	void RenderText(GUIText& text)
	{
		glBindVertexArray(text.GetMesh());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		m_Shader->loadColour(text.GetColour());
		m_Shader->loadTranslation(text.GetPosition());
		glDrawArrays(GL_TRIANGLES, 0, text.GetVertexCount());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}

	void EndRendering()
	{
		m_Shader->Stop();
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

};