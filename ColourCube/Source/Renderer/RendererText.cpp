#include "RendererText.h"
#include "../Shader/ShaderBase.h"
#include "../UI/UIText.h"

namespace Renderer
{
	RendererText::RendererText()
		: m_Shader(std::make_unique<Shader::ShaderBase>("Text"))
	{
		
	}

	RendererText::~RendererText()
	{

	}

	void RendererText::Prepare()
	{
		m_Shader->Bind();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
	}

	void RendererText::Render(UI::UIText* text)
	{
		text->Bind();

		m_Shader->SetUniform3f("u_Colour", text->GetColour());
		m_Shader->SetUniform2f("u_Translation", text->GetPosition());

		glDrawElements(GL_TRIANGLES, text->GetCount(), GL_UNSIGNED_INT, nullptr);

		text->Unbind();
	}

	void RendererText::EndRendering()
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		m_Shader->Unbind();
	}

}