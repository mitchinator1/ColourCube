#ifndef STATE_GAME_H
#define STATE_GAME_H
#include <memory>
#include "StateBase.h"

class Level;

namespace State
{
	class StateGame : public State::StateBase
	{
	private:
		std::unique_ptr<Level> m_Level;

	public:
		StateGame(std::shared_ptr<Display>& display);
		~StateGame();

		void HandleEvents(GameEngine* game)			override;
		void Update(GameEngine* game)				override;
		void Render()						const	override;
	};
}

#endif