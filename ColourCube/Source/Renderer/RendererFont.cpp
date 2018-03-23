#include "RendererFont.h"

namespace Renderer
{
	RendererFont::RendererFont()
		: m_Shader(std::make_unique<Shader::ShaderFont>())
	{
		//Text::GUIText text
		//Text::FontType font = text.getFont();
		//Text::TextMeshData data = font.loadText(text);
		//int vao = loader.loadToVAO(data.getVertexPositions(), data.getTextureCoords());
		//text.setMeshInfo(vao, data.getVertexCount());
		m_FontType = new Text::FontType("Arial");
		m_GUIText = new Text::GUIText("Testing Text", 1.0f, *m_FontType, { 0.0f, 0.3f }, 1.0f, false);

		//Text::TextMeshData data = m_FontType->LoadText(*m_GUIText);
		//m_GUIText->SetMesh(data.GetVertexPositions(), data.GetTextureCoords());
		//LoadVAO(data.GetVertexPositions(), data.GetTextureCoords());
		//GUIText->SetMeshInfo(m_VAO, m_Indices);
	}

	RendererFont::~RendererFont()
	{

	}

	void RendererFont::LoadVAO(std::vector<float>& vertexPositions, std::vector<float>& textureCoords)
	{
		std::vector<float> vertices;

		for (unsigned int i = 0; i < vertexPositions.size(); ++i)
		{
			vertices.emplace_back(vertexPositions[i]);
			vertices.emplace_back(textureCoords[i]);
		}

		VertexArray vao;
		VertexBuffer vbo(vertices);
		VertexBufferLayout layout;

		layout.Push<float>(3);
		vao.AddBuffer(vbo, layout);

	}

	//void RendererFont::Render(std::unordered_map<Text::FontType, std::vector<Text::GUIText>>& texts)
	//{
	//	Prepare();
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
	//	EndRendering();
	//}

	void RendererFont::Render()
	{
		Prepare();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_FontType->GetTextureAtlas());

		RenderText(*m_GUIText);

		EndRendering();
	}

	void RendererFont::Prepare()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		m_Shader->Bind();
	}

	void RendererFont::RenderText(Text::GUIText& text)
	{
		text.Bind();
		//glBindVertexArray(text.GetMesh());
		//glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);
		m_Shader->LoadColour(text.GetColour());
		m_Shader->LoadTranslation(text.GetPosition());
		glDrawArrays(GL_TRIANGLES, 0, text.GetVertexCount());
		//glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);
		//glBindVertexArray(0);
		text.Unbind();
	}

	void RendererFont::EndRendering()
	{
		m_Shader->Unbind();
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}
}