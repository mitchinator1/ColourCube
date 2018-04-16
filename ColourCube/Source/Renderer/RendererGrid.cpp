#include "RendererGrid.h"
#include "../Camera/CameraBase.h"
#include "../Shader/ShaderBase.h"
#include "../Level/Gridline.h"

Renderer::RendererGrid::RendererGrid(std::shared_ptr<Camera::CameraBase> camera)
	: m_Camera(camera), m_Shader(std::make_unique<Shader::ShaderBase>())
{
	m_Shader->Bind();
	m_Shader->SetUniformMat4("u_Projection", m_Camera->GetProjectionMatrix());
	m_Shader->SetUniformMat4("u_View", m_Camera->GetViewMatrix());
	m_Shader->SetUniform3f("u_ViewPos", m_Camera->GetPosition());
	m_Shader->SetUniform3f("u_LightColour", 1.0f, 10.0f, 1.0f);
	m_Shader->SetUniform3f("u_LightPos", 1.0f, 10.0f, 5.0f);
	m_Shader->Unbind();
}

Renderer::RendererGrid::~RendererGrid()
{

}

void Renderer::RendererGrid::Render(Gridline & grid) const
{
	Prepare();

	grid.Bind();

	m_Shader->SetUniformMat4("u_Model", grid.GetModelMatrix());
	glDrawElements(GL_TRIANGLES, grid.GetCount(), GL_UNSIGNED_INT, nullptr);

	grid.Unbind();

	EndRendering();
}

void Renderer::RendererGrid::Prepare() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3.0f);

	m_Shader->Bind();

	m_Shader->SetUniformMat4("u_View", m_Camera->GetViewMatrix());
	m_Shader->SetUniform3f("u_ViewPos", m_Camera->GetPosition());
}

void Renderer::RendererGrid::EndRendering() const
{
	m_Shader->Unbind();

	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
