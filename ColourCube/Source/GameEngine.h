#pragma once
#include <vector>
#include "States/BasicState.h"

class GameEngine
{
private:
	bool m_Running;
	std::vector<BasicState*> m_States;

public:
	void Init();
	void CleanUp();

	void ChangeState(BasicState* state);
	void PushState(BasicState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	inline bool Running() { return m_Running; }
	inline void Quit() { m_Running = false; }
};