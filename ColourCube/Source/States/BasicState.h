#pragma once
struct GLFWwindow;

class BasicState
{
public:
	virtual void Init(GLFWwindow* window) = 0;
	virtual void CleanUp() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};