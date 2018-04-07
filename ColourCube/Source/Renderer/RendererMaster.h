#ifndef RENDERER_MASTER_H
#define RENDERER_MASTER_H
#include <memory>
#include "../UI/UIMaster.h"

struct GLFWwindow;
namespace Camera { class CameraBase; }
class Entity;

namespace Renderer
{
	class RendererEntity;
	class RendererUI;

	class RendererMaster
	{
	private:
		GLFWwindow* m_Window;

		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<RendererEntity> m_RendererEntity;
		std::unique_ptr<RendererUI> m_RendererUI;

	public:
		RendererMaster(GLFWwindow* window, std::shared_ptr<Camera::CameraBase> camera);
		~RendererMaster();

		void Clear() const;

		void PrepareEntity();

		void Render(Entity* entity);
		void Render(UI::UIMaster& ui);

		void EndRenderingEntity();

		void Swap() const;
	};
}

#endif