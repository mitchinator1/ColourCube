#pragma once
#include "BasicInput.h"
#include "GLFW/glfw3.h"

class GridInput : public BasicInput
{
private:
	GLFWwindow* m_Window;
	std::vector<Key> m_Keys = {
		{ GLFW_KEY_E }
	};
public:
	GridInput(GLFWwindow* window);

	void HandleEvents();
	void Update(Entity& entity);
	Key& GetKey(int key);
};