#include "RendererLevel.h"
#include "../Camera/CameraBase.h"
#include "../Shader/ShaderBase.h"
#include "GLFW/glfw3.h"

namespace Renderer
{
	RendererLevel::RendererLevel(std::shared_ptr<Camera::CameraBase> camera)
		: RendererBase(camera)
	{
		m_Shader->Bind();
		m_Shader->SetUniform3f("u_ViewPos", m_Camera->GetPosition());
		m_Shader->SetUniform3f("u_LightColour", 0.9f, 0.9f, 0.85f);
		m_Shader->SetUniform3f("u_LightPos", 1.0f, 10.0f, 3.0f);
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

	void RendererLevel::CleanUp() const
	{
		m_Shader->Unbind();

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
}