#pragma once
#include "../Entity.h"
#include "../Shader/ShaderBase.h"
#include "../Camera/CameraBase.h"
#include "RendererFont.h"

#include <memory>

namespace Renderer
{
	class RendererEntity
	{
	private:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		Shader::ShaderBase m_Shader;

	public:
		RendererEntity(std::shared_ptr<Camera::CameraBase> camera);
		~RendererEntity();

		void Prepare();
		void Render(Entity* entity);
		void EndRendering();

	};
}