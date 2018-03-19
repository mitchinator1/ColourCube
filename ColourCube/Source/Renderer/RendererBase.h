#pragma once
#include "../Entity.h"
#include "../Shader/ShaderBase.h"
#include "../Camera/CameraBase.h"

namespace Renderer
{
	class RendererBase
	{
	private:
		Camera::CameraBase* m_Camera;
		Shader::ShaderBase m_Shader;
	public:
		RendererBase(Camera::CameraBase* camera);
		~RendererBase();

		void Clear() const;
		void Render(Entity* entity);
	};
}