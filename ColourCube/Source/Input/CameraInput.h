#pragma once
#include "GLFW/glfw3.h"
#include "BasicInput.h"

class CameraInput : public BasicInput
{
private:
	GLFWwindow* m_Window;
	std::vector<Key> m_Keys = {
		{ GLFW_KEY_W },
	{ GLFW_KEY_S },
	{ GLFW_KEY_A },
	{ GLFW_KEY_D },
	{ GLFW_KEY_SPACE },
	{ GLFW_KEY_LEFT_SHIFT }
	};
	float m_Speed = 1.0f;

public:
	CameraInput(GLFWwindow* window);
	~CameraInput();

	void HandleEvents();
	void Update(Entity& entity);
	Key& GetKey(int key);

};