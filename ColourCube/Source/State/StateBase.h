#ifndef STATE_BASE_H
#define STATE_BASE_H
#include <memory>
#include "../GameEngine.h"

struct Display;

namespace State
{
	class StateBase
	{
	public:
		StateBase() {}
		virtual ~StateBase() {}

		virtual void Init(std::shared_ptr<Display> display) = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents(GameEngine* game) = 0;
		virtual void Update(GameEngine* game) = 0;
		virtual void Render() const = 0;

		void ChangeState(GameEngine* game, std::unique_ptr<State::StateBase> state)
		{
			game->ChangeState(std::move(state));
		}
	};
}

#endif