#pragma once
#include "BasicInput.h"
#include <vector>

class GridInput : public BasicInput
{
private:
	GLFWwindow* m_Window;
	std::vector<Key> m_Keys = {
		{ GLFW_KEY_E,	Command::CHANGE_COLOUR },
		{ GLFW_KEY_R,	Command::CHANGE_COLOUR_2 } // Test Command
	};

public:
	GridInput(GLFWwindow* window);
	~GridInput() {}

	void HandleEvents();
	void Update(Entity& entity);
};