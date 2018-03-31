#include "RendererUI.h"
#include "../Shader/ShaderBase.h"
#include "../UI/Font/FontType.h"

namespace Renderer
{
	RendererUI::RendererUI()
		: m_TextShader(std::make_unique<Shader::ShaderBase>("Text")) 
		, m_ElementShader(std::make_unique<Shader::ShaderBase>("UI"))
	{

	}

	RendererUI::~RendererUI()
	{

	}

	void RendererUI::Render(UI::UIMaster* ui)
	{
		PrepareElement();
		ui->Bind();

		glDrawElements(GL_TRIANGLES, ui->GetCount(), GL_UNSIGNED_INT, nullptr);

		ui->Unbind();
		EndRenderingElement();

		PrepareText();
		for (auto& fonts : ui->GetTexts())
		{
			fonts.first->Bind();
			for (auto& text : fonts.second)
			{
				text.Bind();

				m_TextShader->SetUniform3f("u_Colour", text.GetColour());
				m_TextShader->SetUniform2f("u_Translation", text.GetPosition());

				glDrawElements(GL_TRIANGLES, text.GetCount(), GL_UNSIGNED_INT, nullptr);

				text.Unbind();
			}
			fonts.first->Unbind();
		}
		EndRenderingText();
	}

	void RendererUI::PrepareText()
	{
		m_TextShader->Bind();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
	}

	void RendererUI::PrepareElement()
	{
		m_ElementShader->Bind();
		glEnable(GL_DEPTH_TEST);
	}

	void RendererUI::EndRenderingText()
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		m_TextShader->Unbind();
	}

	void RendererUI::EndRenderingElement()
	{
		glDisable(GL_DEPTH_TEST);
		m_ElementShader->Unbind();
	}

}