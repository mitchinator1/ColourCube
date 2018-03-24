#pragma once
#include "../Camera/CameraBase.h"
#include "RendererEntity.h"
#include "RendererFont.h"

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
		std::unique_ptr<RendererFont> m_RendererFont;

	public:
		RendererMaster(GLFWwindow* window, std::shared_ptr<Camera::CameraBase> camera);
		~RendererMaster();

		void Clear() const;

		void PrepareEntity();
		void PrepareText();

		void Render(Entity* entity);
		void Render(Text::GUIText* text);

		void EndRenderingEntity();
		void EndRenderingText();

		void Swap() const;
	};
}