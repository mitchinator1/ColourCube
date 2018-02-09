#pragma once
#include "../GameEngine.h"
struct GLFWwindow;

class BasicState
{
public:
	BasicState() {}
	virtual ~BasicState() {}

	virtual void Init(GLFWwindow* window) = 0;
	virtual void CleanUp() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(GameEngine* game) = 0;
	virtual void Update(GameEngine* game) = 0;
	virtual void Draw(GameEngine* game) = 0;

	void ChangeState(GameEngine* game, BasicState* state)
	{
		game->ChangeState(state);
	}
};