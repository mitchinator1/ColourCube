#ifndef RENDERER_BASE_H
#define RENDERER_BASE_H
#include <memory>
#include <string>

namespace Camera { class CameraBase; }
namespace Shader { class ShaderBase; }
class Mesh;

namespace Renderer
{
	class RendererBase
	{
	protected:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Shader::ShaderBase> m_Shader;

	public:
		RendererBase(std::shared_ptr<Camera::CameraBase> camera, const std::string& shader = "Basic");
		virtual ~RendererBase();

		virtual void Prepare()			const;
		virtual void Render(Mesh* mesh) const;
		virtual void CleanUp()			const;

	};
}

#endif