#include "RendererEntity.h"
#include "../Camera/CameraBase.h"
#include "../Shader/ShaderBase.h"
#include "../Entity.h"

namespace Renderer
{
	RendererEntity::RendererEntity(std::shared_ptr<Camera::CameraBase> camera)
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

	RendererEntity::~RendererEntity()
	{

	}

	void RendererEntity::Prepare()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		m_Shader->Bind();

		m_Shader->SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader->SetUniform3f("u_ViewPos", m_Camera->GetPosition());
	}

	void RendererEntity::Render(Entity* entity)
	{
		m_Shader->SetUniformMat4("u_Model", entity->GetModelMatrix());
		//Bring GL code here, instead of in Entity
		entity->Draw();
	}

	void RendererEntity::EndRendering()
	{
		m_Shader->Unbind();

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}
}