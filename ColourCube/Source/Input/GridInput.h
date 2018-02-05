#pragma once
#include "BasicInput.h"
#include "GLFW/glfw3.h"

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

	void HandleEvents();
	void Update(Entity& entity);
	Key& GetKey(int key);
};