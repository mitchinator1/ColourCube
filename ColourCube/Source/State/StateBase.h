#pragma once
#include "../GameEngine.h"
#include <memory>

struct GLFWwindow;

namespace State
{
	class StateBase
	{
	public:
		StateBase() {}
		virtual ~StateBase() {}

		virtual void Init(GLFWwindow* window) = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents(GameEngine* game) = 0;
		virtual void Update(GameEngine* game) = 0;
		virtual void Render() = 0;

		void ChangeState(GameEngine* game, std::unique_ptr<State::StateBase> state)
		{
			game->ChangeState(std::move(state));
		}
	};
}