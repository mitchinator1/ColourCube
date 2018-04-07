#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <vector>
#include <memory>
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace State { class StateBase; }

class GameEngine
{
private:
	bool m_Running;
	std::string m_Title;
	int m_Width;
	int m_Height;
	std::vector<std::unique_ptr<State::StateBase>> m_States;
	GLFWwindow* m_Window;

public:
	GameEngine(const std::string& title, int width, int height);
	~GameEngine();

	void Init();

	void ChangeState(std::unique_ptr<State::StateBase> state);
	void PushState(std::unique_ptr<State::StateBase> state);
	void PopState();

	void HandleEvents();
	void Update();
	void Render();

	void Quit();

	inline bool Running() const { return m_Running; }
	inline GLFWwindow* GetWindow() const { return m_Window; }
};

#endif