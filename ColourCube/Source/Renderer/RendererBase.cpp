#include "RendererBase.h"
#include "GLFW/glfw3.h"

namespace Renderer
{
	RendererBase::RendererBase(Camera::CameraBase* camera)
		: m_Camera(camera)
	{
		m_Shader.Bind();
		m_Shader.SetUniformMat4("u_Projection", m_Camera->GetProjectionMatrix());
		m_Shader.SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader.SetUniform3f("u_LightColour", 1.0f, 1.0f, 1.0f);
		m_Shader.SetUniform3f("u_LightPos", 1.0f, 10.0f, 5.0f);
		m_Shader.Unbind();
	}

	RendererBase::~RendererBase()
	{
		delete m_Camera;
	}

	void RendererBase::Render(Entity* entity)
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		m_Shader.Bind();

		m_Shader.SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader.SetUniform3f("u_ViewPos", m_Camera->GetPosition());

		m_Shader.SetUniformMat4("u_Model", entity->GetModelMatrix());
		entity->Draw();

		m_Shader.Unbind();

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}

	void RendererBase::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}