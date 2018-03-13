#pragma once
#include "StateBase.h"

namespace State
{
	class StateMenu : public State::StateBase
	{
	public:
		StateMenu();
		~StateMenu();

		void Init(GLFWwindow* window);

		void Pause();
		void Resume();

		void HandleEvents(GameEngine* game);
		void Update(GameEngine* game);
		void Draw(GameEngine* game);
	};
}