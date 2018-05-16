#ifndef STATE_EDITOR_H
#define STATE_EDITOR_H
#include "StateBase.h"
#include <memory>

namespace Camera { class CameraBase; }
namespace Renderer { 
	class RendererMaster;
	class RendererGrid;
}
namespace UI { class UIMaster; }
class Level;
class Gridline;

namespace State
{
	class StateEditor : public StateBase
	{
	private:
		std::unique_ptr<UI::UIMaster> m_UI;
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Renderer::RendererMaster> m_Renderer;
		std::unique_ptr<Level> m_Level;
		std::unique_ptr<Gridline> m_Grid;
		std::unique_ptr<Renderer::RendererGrid> m_RendererGrid;

		std::shared_ptr<Display> m_Display;

	public:
		StateEditor() noexcept;
		~StateEditor();

		void Init(std::shared_ptr<Display> display);

		void Pause();
		void Resume();

		void HandleEvents(GameEngine* game);
		void Update(GameEngine* game);
		void Render() const;

	};
}


#endif