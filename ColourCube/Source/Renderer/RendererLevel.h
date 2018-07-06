#ifndef RENDERER_LEVEL_H
#define RENDERER_LEVEL_H
#include <memory>

namespace Camera { class CameraBase; }
namespace Shader { class ShaderBase; }
class Mesh;

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

		void Render(Mesh* mesh)		const;

	private:
		void Prepare()				const;
		void EndRendering()			const;

	};
}

#endif