#pragma once

class BasicState
{
public:
	virtual void Init() = 0;
	virtual void CleanUp() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};