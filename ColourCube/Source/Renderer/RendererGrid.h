#ifndef RENDERER_GRID_H
#define RENDERER_GRID_H
#include <memory>

namespace Camera { class CameraBase; }
namespace Shader { class ShaderBase; }
class Mesh;

namespace Renderer
{
	class RendererGrid
	{
	private:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Shader::ShaderBase> m_Shader;

	public:
		RendererGrid(std::shared_ptr<Camera::CameraBase> camera);
		~RendererGrid();

		void Render(Mesh* mesh) const;

	private:
		void Prepare() const;
		void EndRendering() const;
	};
}

#endif