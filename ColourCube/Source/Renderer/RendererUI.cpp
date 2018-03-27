#include "RendererUI.h"

namespace Renderer
{
	RendererUI::RendererUI()
		: m_Shader(std::make_unique<Shader::ShaderUI>())
	{

	}

	RendererUI::~RendererUI()
	{

	}

	void RendererUI::Prepare()
	{
		m_Shader->Bind();
		glEnable(GL_DEPTH_TEST);
	}

	void RendererUI::Render(UI::UIMaster* ui)
	{
		ui->Bind();

		glDrawElements(GL_TRIANGLES, ui->GetCount(), GL_UNSIGNED_INT, nullptr);

		ui->Unbind();
	}

	void RendererUI::EndRendering()
	{
		glDisable(GL_DEPTH_TEST);
		m_Shader->Unbind();
	}

}