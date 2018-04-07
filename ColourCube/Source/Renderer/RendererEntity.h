#ifndef RENDERER_ENTITY_H
#define RENDERER_ENTITY_H
#include <memory>

namespace Camera { class CameraBase; }
namespace Shader { class ShaderBase; }
class Entity;

namespace Renderer
{
	class RendererEntity
	{
	private:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Shader::ShaderBase> m_Shader;

	public:
		RendererEntity(std::shared_ptr<Camera::CameraBase> camera);
		~RendererEntity();

		void Prepare();
		void Render(Entity* entity);
		void EndRendering();

	};
}

#endif