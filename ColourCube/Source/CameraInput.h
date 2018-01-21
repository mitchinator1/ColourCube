#pragma once
#include "GLFW/glfw3.h"
#include "BasicInput.h"

class CameraInput : public BasicInput
{
public:
	CameraInput();
	~CameraInput();

	void Update(Entity& entity);
	Key& GetKey(int key);
	void GetKeyStates();
	void Bind(GLFWwindow* window);

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
};