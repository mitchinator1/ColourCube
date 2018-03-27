#include "RendererMaster.h"
#include "GLFW/glfw3.h"

namespace Renderer
{
	RendererMaster::RendererMaster(GLFWwindow* window, std::shared_ptr<Camera::CameraBase> camera)
		: m_Window(window), m_Camera(camera)
		, m_RendererEntity(std::make_unique<RendererEntity>(camera))
		, m_RendererFont(std::make_unique<RendererFont>())
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

	void RendererMaster::PrepareText()
	{
		m_RendererFont->Prepare();
	}

	void RendererMaster::PrepareUI()
	{
		m_RendererUI->Prepare();
	}

	void RendererMaster::Render(Entity* entity)
	{
		m_RendererEntity->Render(entity);
	}

	void RendererMaster::Render(Text::GUIText* text)
	{
		m_RendererFont->Render(text);
	}
	
	void RendererMaster::Render(UI::UIMaster* ui)
	{
		m_RendererUI->Render(ui);
	}

	void RendererMaster::EndRenderingEntity()
	{
		m_RendererEntity->EndRendering();
	}

	void RendererMaster::EndRenderingText()
	{
		m_RendererFont->EndRendering();
	}

	void RendererMaster::EndRenderingUI()
	{
		m_RendererUI->EndRendering();
	}
	
	void RendererMaster::Swap() const
	{
		glfwSwapBuffers(m_Window);
	}
}