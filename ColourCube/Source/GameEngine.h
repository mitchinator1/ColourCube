#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <string>
#include "States/BasicState.h"

class GameEngine
{
private:
	bool m_Running = false;
	std::string m_Title;
	int m_Width;
	int m_Height;
	std::vector<BasicState*> m_States;
	GLFWwindow* m_Window;

public:
	GameEngine(const std::string title, int width, int height);
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