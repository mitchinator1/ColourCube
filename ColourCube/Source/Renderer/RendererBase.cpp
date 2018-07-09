#include "RendererBase.h"
#include "../Camera/CameraBase.h"
#include "../Shader/ShaderBase.h"
#include "../Mesh/Mesh.h"
#include "GLFW/glfw3.h"

namespace Renderer
{
	RendererBase::RendererBase(std::shared_ptr<Camera::CameraBase> camera, const std::string& shader)
		: m_Camera(camera), m_Shader(std::make_unique<Shader::ShaderBase>(shader))
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_Projection", m_Camera->GetProjectionMatrix());
		m_Shader->SetUniformMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader->Unbind();
	}

	RendererBase::~RendererBase()
	{

	}

	void RendererBase::Prepare() const
	{
		m_Shader->Bind();
	}

	void RendererBase::Render(Mesh* mesh) const
	{
		Prepare();

		mesh->Bind();

		m_Shader->SetUniformMat4("u_Model", mesh->GetModelMatrix());
		glDrawElements(mesh->GetMode(), mesh->GetCount(), GL_UNSIGNED_INT, nullptr);

		mesh->Unbind();

		CleanUp();
	}

	void RendererBase::CleanUp() const
	{
		m_Shader->Unbind();
	}
}