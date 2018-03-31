#ifndef RENDERER_MASTER_H
#define RENDERER_MASTER_H
#include "../Camera/CameraBase.h"
#include "RendererEntity.h"
#include "RendererText.h"
#include "RendererUI.h"

#include <memory>

struct GLFWwindow;

namespace Renderer
{
	class RendererMaster
	{
	private:
		GLFWwindow* m_Window;
		std::shared_ptr<Camera::CameraBase> m_Camera;

		std::shared_ptr<Text::FontType> m_Font;

		std::unique_ptr<RendererEntity> m_RendererEntity;
		std::unique_ptr<RendererText> m_RendererFont;
		std::unique_ptr<RendererUI> m_RendererUI;

	public:
		RendererMaster(GLFWwindow* window, std::shared_ptr<Camera::CameraBase> camera);
		~RendererMaster();

		void Clear() const;

		void PrepareEntity();

		void Render(Entity* entity);
		void Render(UI::UIMaster* ui);

		void EndRenderingEntity();

		void Swap() const;
	};
}

#endif