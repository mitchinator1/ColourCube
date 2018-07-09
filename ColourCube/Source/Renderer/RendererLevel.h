#ifndef RENDERER_LEVEL_H
#define RENDERER_LEVEL_H
#include <memory>
#include "RendererBase.h"

namespace Renderer
{
	class RendererLevel : public RendererBase
	{
	public:
		RendererLevel(std::shared_ptr<Camera::CameraBase> camera);
		~RendererLevel();
		
	private:
		void Prepare()		const	override;
		void CleanUp()		const	override;

	};
}

#endif