#pragma once
#include "../Entity.h"
#include "../Shader/ShaderBase.h"
#include "../Camera/CameraBase.h"
#include "RendererFont.h"

#include <memory>

namespace Renderer
{
	class RendererBase
	{
	private:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		Shader::ShaderBase m_Shader;
		std::unique_ptr<RendererFont> m_RendererFont;
	public:
		RendererBase(std::shared_ptr<Camera::CameraBase> camera);
		~RendererBase();

		void Clear() const;
		void Render(Entity* entity);
	};
}