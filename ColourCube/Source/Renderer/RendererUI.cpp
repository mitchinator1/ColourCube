#include "RendererUI.h"
#include "../Shader/ShaderBase.h"
#include "../Mesh/Mesh.h"

namespace Renderer
{
	RendererUI::RendererUI() noexcept
		: m_TextShader(std::make_unique<Shader::ShaderBase>("Text")) 
		, m_ElementShader(std::make_unique<Shader::ShaderBase>("UI"))
	{

	}

	RendererUI::~RendererUI()
	{

	}

	void RendererUI::Render(UI::UIMaster* ui) const
	{
		PrepareElement();
		RenderElements(ui->GetElementMesh());
		EndRenderingElement();

		PrepareText();
		for (auto& fonts : ui->GetFontMeshes())
		{
			RenderElements(fonts.get());
		}
		EndRenderingText();

		/* Code for Textboxes
		Might be able to have it drawn with the elements, and with the text.
		if (!ui.GetElements()[UI::TYPE::TEXTBOX].empty())
		{
			PrepareElement();
			RenderElements(ui.GetElements()[UI::TYPE::TEXTBOX]);
			EndRenderingElement();

			PrepareText();
			for (const auto& font : ui.GetTexts())
			{
				font.second.first->Bind();
				{
					const auto& text = font.second.second.back();
					if (text->IsHidden())
						continue;

					text->Bind();

					m_TextShader->SetUniform3f("u_Colour", text->GetColour());
					m_TextShader->SetUniform2f("u_Translation", text->GetPosition());
					glDrawElements(GL_TRIANGLES, text->GetCount(), GL_UNSIGNED_INT, nullptr);

					text->Unbind();
				}
				font.second.first->Unbind();
			}
			EndRenderingText();
		}*/
	}

	void RendererUI::PrepareElement() const
	{
		m_ElementShader->Bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RendererUI::PrepareText() const
	{
		m_TextShader->Bind();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
	}

	void RendererUI::RenderElements(Mesh* mesh) const
	{
		mesh->Bind();

		glDrawElements(mesh->GetMode(), mesh->GetCount(), GL_UNSIGNED_INT, nullptr);

		mesh->Unbind();
	}
	
	void RendererUI::EndRenderingText() const
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		m_TextShader->Unbind();
	}

	void RendererUI::EndRenderingElement() const
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		m_ElementShader->Unbind();
	}

}