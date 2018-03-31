#ifndef RENDERER_ENTITY_H
#define RENDERER_ENTITY_H
#include "../Entity.h"
#include "../Shader/ShaderBase.h"

#include <memory>

namespace Camera { class CameraBase; }

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

#endif