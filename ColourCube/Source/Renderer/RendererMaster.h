#ifndef RENDERER_MASTER_H
#define RENDERER_MASTER_H
#include <memory>

struct GLFWwindow;
namespace Camera { class CameraBase; }
namespace UI { class UIMaster; }
class Mesh;

namespace Renderer
{
	class RendererBase;
	class RendererUI;

	class RendererMaster
	{
	private:
		GLFWwindow* m_Window;

		std::unique_ptr<RendererBase> m_RendererLevel;
		std::unique_ptr<RendererUI> m_RendererUI;

	public:
		RendererMaster(GLFWwindow* window, std::shared_ptr<Camera::CameraBase> camera);
		~RendererMaster();

		void Clear() const;

		void Render(Mesh* mesh)			const;
		void Render(UI::UIMaster* ui)	const;

		void Swap() const;
	};
}

#endif