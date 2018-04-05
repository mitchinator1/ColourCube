#include "RendererMaster.h"
#include "GLFW/glfw3.h"

namespace Renderer
{
	RendererMaster::RendererMaster(GLFWwindow* window, std::shared_ptr<Camera::CameraBase> camera)
		: m_Window(window), m_Camera(camera)
		, m_RendererEntity(std::make_unique<RendererEntity>(camera))
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

	void RendererMaster::PrepareEntity()
	{
		m_RendererEntity->Prepare();
	}

	void RendererMaster::Render(Entity* entity)
	{
		m_RendererEntity->Render(entity);
	}

	void RendererMaster::Render(UI::UIMaster& ui)
	{
		m_RendererUI->Render(ui);
	}

	void RendererMaster::EndRenderingEntity()
	{
		m_RendererEntity->EndRendering();
	}

	void RendererMaster::Swap() const
	{
		glfwSwapBuffers(m_Window);
	}
}