#include "RendererMaster.h"
#include "../Camera/CameraBase.h"
#include "RendererLevel.h"
#include "RendererUI.h"
#include "../UI/UIMaster.h"
#include "../Mesh/Mesh.h"
#include "GLFW/glfw3.h"

namespace Renderer
{
	RendererMaster::RendererMaster(GLFWwindow* window, std::shared_ptr<Camera::CameraBase> camera)
		: m_Window(window)
		, m_RendererLevel(std::make_unique<RendererLevel>(camera))
		, m_RendererUI(std::make_unique<RendererUI>())
	{

	}

	RendererMaster::~RendererMaster()
	{

	}

	void RendererMaster::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererMaster::Render(Mesh* mesh) const
	{
		m_RendererLevel->Render(mesh);
	}

	void RendererMaster::Render(UI::UIMaster* ui) const
	{
		m_RendererUI->Render(ui);
	}

	void RendererMaster::Swap() const
	{
		glfwSwapBuffers(m_Window);
	}
}