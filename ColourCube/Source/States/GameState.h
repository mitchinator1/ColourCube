#pragma once
#include "BasicState.h"

class GameState : public BasicState
{
public:
	void Init();
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();
};