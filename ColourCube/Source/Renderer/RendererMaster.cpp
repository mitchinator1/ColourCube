#include "RendererMaster.h"
#include "GLFW/glfw3.h"

namespace Renderer
{
	RendererMaster::RendererMaster(GLFWwindow* window, std::shared_ptr<Camera::CameraBase> camera)
		: m_Window(window), m_Camera(camera)
		, m_RendererEntity(std::make_unique<RendererEntity>(camera))
		, m_RendererFont(std::make_unique<RendererFont>())
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

	void RendererMaster::PrepareText()
	{
		m_RendererFont->Prepare();
	}

	void RendererMaster::Render(Entity* entity)
	{
		m_RendererEntity->Render(entity);
	}

	void RendererMaster::Render(Text::GUIText* text)
	{
		m_RendererFont->Render(text);
	}

	void RendererMaster::EndRenderingEntity()
	{
		m_RendererEntity->EndRendering();
	}

	void RendererMaster::EndRenderingText()
	{
		m_RendererFont->EndRendering();
	}

	void RendererMaster::Swap() const
	{
		glfwSwapBuffers(m_Window);
	}
}