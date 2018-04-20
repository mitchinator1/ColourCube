#include "RendererUI.h"
#include "../Shader/ShaderBase.h"
#include "../UI/Font/FontType.h"
#include "../UI/UIText.h"
#include "../UI/UIBackground.h"

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

	void RendererUI::Render(UI::UIMaster& ui)
	{
		PrepareElement();
		for (auto& element : ui.GetBackgrounds())
		{
			element->Bind();

			m_ElementShader->SetUniform1f("u_Alpha", element->GetAlpha());

			glDrawElements(GL_TRIANGLES, element->GetCount(), GL_UNSIGNED_INT, nullptr);

			element->Unbind();
		}
		EndRenderingElement();

		PrepareText();
		for (const auto& fonts : ui.GetTexts())
		{
			fonts.second.first->Bind();
			for (const auto& text : fonts.second.second)
			{
				text->Bind();

				m_TextShader->SetUniform3f("u_Colour", text->GetColour());
				m_TextShader->SetUniform2f("u_Translation", text->GetPosition());

				glDrawElements(GL_TRIANGLES, text->GetCount(), GL_UNSIGNED_INT, nullptr);

				text->Unbind();
			}
			fonts.second.first->Unbind();
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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RendererUI::EndRenderingText()
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		m_TextShader->Unbind();
	}

	void RendererUI::EndRenderingElement()
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		m_ElementShader->Unbind();
	}

}