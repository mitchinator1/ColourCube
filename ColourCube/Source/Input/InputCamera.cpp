#include "InputCamera.h"

namespace Input
{
	Camera::Camera(GLFWwindow* window)
		: m_Window(window)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::HandleEvents()
	{
		for (auto& key : m_Keys)
			key.Pressed = glfwGetKey(m_Window, key.ID);
	}

	void Camera::Update(Entity& entity)
	{
		for (const auto& key : m_Keys)
			if (!key.Pressed)
				continue;
			else
				entity.Action(key.Action);
	}
}