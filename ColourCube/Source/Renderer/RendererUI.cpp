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
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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