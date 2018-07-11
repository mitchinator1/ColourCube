#ifndef STATE_EDITOR_H
#define STATE_EDITOR_H
#include "StateBase.h"

namespace Renderer { class RendererGrid; }
class Level;
class Gridline;

namespace State
{
	class StateEditor : public StateBase
	{
	private:
		std::unique_ptr<Renderer::RendererGrid> m_RendererGrid;
		std::unique_ptr<Level> m_Level;
		std::unique_ptr<Gridline> m_Grid;

	public:
		StateEditor(std::shared_ptr<Display>& display);
		~StateEditor();

		void HandleEvents(GameEngine* game)			override;
		void Update(GameEngine* game)				override;
		void Render()						const	override;

	};
}

#endif