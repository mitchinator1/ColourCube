#ifndef RENDERER_LEVEL_H
#define RENDERER_LEVEL_H
#include <memory>

namespace Camera { class CameraBase; }
namespace Shader { class ShaderBase; }
class Level;

namespace Renderer
{
	class RendererLevel
	{
	private:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Shader::ShaderBase> m_Shader;

	public:
		RendererLevel(std::shared_ptr<Camera::CameraBase> camera);
		~RendererLevel();

		void Prepare() const;
		void Render(Level& level) const;
		void EndRendering() const;

	};
}

#endif