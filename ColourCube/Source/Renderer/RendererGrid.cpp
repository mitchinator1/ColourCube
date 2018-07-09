#include "RendererGrid.h"
#include "../Camera/CameraBase.h"
#include "../Shader/ShaderBase.h"
#include "GLFW/glfw3.h"

namespace Renderer
{
	RendererGrid::RendererGrid(std::shared_ptr<Camera::CameraBase> camera)
		: RendererBase(camera, "Grid")
	{

	}

	RendererGrid::~RendererGrid()
	{

	}

	void RendererGrid::Prepare() const
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(LINE_WIDTH);

		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_View", m_Camera->GetViewMatrix());
	}

	void RendererGrid::CleanUp() const
	{
		m_Shader->Unbind();

		glLineWidth(1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
