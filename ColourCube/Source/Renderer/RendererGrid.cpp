#include "RendererGrid.h"
#include "../Camera/CameraBase.h"
#include "../Shader/ShaderBase.h"
#include "../Mesh/Mesh.h"
#include "GLFW/glfw3.h"

Renderer::RendererGrid::RendererGrid(std::shared_ptr<Camera::CameraBase> camera)
	: m_Camera(camera), m_Shader(std::make_unique<Shader::ShaderBase>("Grid"))
{
	m_Shader->Bind();
	m_Shader->SetUniformMat4("u_Projection", m_Camera->GetProjectionMatrix());
	m_Shader->SetUniformMat4("u_View", m_Camera->GetViewMatrix());
	m_Shader->Unbind();
}

Renderer::RendererGrid::~RendererGrid()
{

}

void Renderer::RendererGrid::Render(Mesh* mesh) const
{
	Prepare();

	mesh->Bind();

	m_Shader->SetUniformMat4("u_Model", mesh->GetModelMatrix());
	glDrawElements(mesh->GetMode(), mesh->GetCount(), GL_UNSIGNED_INT, nullptr);

	mesh->Unbind();

	EndRendering();
}

void Renderer::RendererGrid::Prepare() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(5.0f);

	m_Shader->Bind();
	m_Shader->SetUniformMat4("u_View", m_Camera->GetViewMatrix());
}

void Renderer::RendererGrid::EndRendering() const
{
	m_Shader->Unbind();

	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
