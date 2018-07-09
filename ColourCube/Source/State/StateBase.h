#ifndef STATE_BASE_H
#define STATE_BASE_H
#include <memory>
#include "../GameEngine.h"
#include "../Display.h"

namespace State
{
	class StateBase
	{
	protected:
		std::shared_ptr<Display> m_Display;

	public:
		StateBase(std::shared_ptr<Display>& display) : m_Display(display) {}
		virtual ~StateBase() {}

		virtual void Pause() {};
		virtual void Resume() {};

		virtual void HandleEvents(GameEngine* game)			= 0;
		virtual void Update(GameEngine* game)				= 0;
		virtual void Render()						const	= 0;

		void ChangeState(GameEngine* game, std::unique_ptr<State::StateBase> state)
		{
			game->ChangeState(std::move(state));
		}
	};
}

#endif