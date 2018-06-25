#include "RendererLevel.h"
#include "../Camera/CameraBase.h"
#include "../Shader/ShaderBase.h"
#include "../Level/Level.h"

namespace Renderer
{
	RendererLevel::RendererLevel(std::shared_ptr<Camera::CameraBase> camera)
		: m_Camera(camera), m_Shader(std::make_unique<Shader::ShaderBase>())
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_Projection", m_Camera->GetProjectionMatrix());
		m_Shader->SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader->SetUniform3f("u_ViewPos", m_Camera->GetPosition());
		m_Shader->SetUniform3f("u_LightColour", 1.0f, 1.0f, 1.0f);
		m_Shader->SetUniform3f("u_LightPos", 1.0f, 10.0f, 5.0f);
		m_Shader->Unbind();
	}

	RendererLevel::~RendererLevel()
	{

	}

	void RendererLevel::Prepare() const
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Shader->Bind();

		m_Shader->SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader->SetUniform3f("u_ViewPos", m_Camera->GetPosition());
	}

	void RendererLevel::Render(Level& level) const
	{
		Prepare();

		level.Bind();
		m_Shader->SetUniformMat4("u_Model", level.GetModelMatrix());
		glDrawElements(GL_TRIANGLES, level.GetCount(), GL_UNSIGNED_INT, nullptr);
		level.Unbind();

		EndRendering();
	}

	void RendererLevel::EndRendering() const
	{
		m_Shader->Unbind();

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
}