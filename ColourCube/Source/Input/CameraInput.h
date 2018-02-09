#pragma once
#include "BasicInput.h"
#include <vector>

class CameraInput : public BasicInput
{
private:
	GLFWwindow* m_Window;
	std::vector<Key> m_Keys = {
	{ GLFW_KEY_W,			Command::FORWARD },
	{ GLFW_KEY_S,			Command::BACKWARD },
	{ GLFW_KEY_A,			Command::LEFT },
	{ GLFW_KEY_D,			Command::RIGHT },
	{ GLFW_KEY_SPACE,		Command::UP },
	{ GLFW_KEY_LEFT_SHIFT,	Command::DOWN }
	};
	float m_Speed = 1.0f;

public:
	CameraInput(GLFWwindow* window);
	~CameraInput();

	void HandleEvents();
	void Update(Entity& entity);

};