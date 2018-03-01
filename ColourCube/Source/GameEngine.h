#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <string>
#include <memory>

namespace State
{
	class Basic;
}

class GameEngine
{
private:
	bool m_Running;
	std::string m_Title;
	int m_Width;
	int m_Height;
	std::vector<State::Basic*> m_States;
	GLFWwindow* m_Window;

public:
	GameEngine(const std::string& title, int width, int height);
	~GameEngine();

	void Init();

	void ChangeState(State::Basic* state);
	void PushState(State::Basic* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	void Quit();

	inline bool Running() const { return m_Running; }
	inline GLFWwindow* GetWindow() const { return m_Window; }
};