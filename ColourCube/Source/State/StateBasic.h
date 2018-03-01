#pragma once
#include "../GameEngine.h"

struct GLFWwindow;

namespace State
{
	class Basic
	{
	public:
		Basic() {}
		virtual ~Basic() {}

		virtual void Init(GLFWwindow* window) = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents(GameEngine* game) = 0;
		virtual void Update(GameEngine* game) = 0;
		virtual void Draw(GameEngine* game) = 0;

		void ChangeState(GameEngine* game, Basic* state)
		{
			game->ChangeState(state);
		}
	};
}