#ifndef RENDERER_MASTER_H
#define RENDERER_MASTER_H
#include <memory>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct GLFWwindow;
namespace Camera { class CameraBase; }
namespace UI { class UIMaster; }
class Level;

namespace Renderer
{
	class RendererLevel;
	class RendererUI;

	class RendererMaster
	{
	private:
		GLFWwindow* m_Window;

		std::unique_ptr<RendererLevel> m_RendererLevel;
		std::unique_ptr<RendererUI> m_RendererUI;

	public:
		RendererMaster(GLFWwindow* window, std::shared_ptr<Camera::CameraBase> camera);
		~RendererMaster();

		void Clear() const;

		void Render(Level& level) const;
		void Render(UI::UIMaster& ui) const;

		void Swap() const;
	};
}

#endif