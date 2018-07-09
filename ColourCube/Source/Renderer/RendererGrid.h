#ifndef RENDERER_GRID_H
#define RENDERER_GRID_H
#include "RendererBase.h"

namespace Renderer
{
	class RendererGrid : public RendererBase
	{
	private:
		const float LINE_WIDTH = 5.0f;

	public:
		RendererGrid(std::shared_ptr<Camera::CameraBase> camera);
		~RendererGrid();

	private:
		void Prepare()		const	override;
		void CleanUp()		const	override;
	};
}

#endif