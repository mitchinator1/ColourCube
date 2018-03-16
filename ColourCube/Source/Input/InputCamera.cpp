#include "InputCamera.h"

namespace Input
{
	InputCamera::InputCamera(GLFWwindow* window)
		: m_Window(window)
	{

	}

	InputCamera::~InputCamera()
	{
		
	}

	void InputCamera::HandleEvents(Entity& entity)
	{
		for (auto& key : m_Keys)
			key.Pressed = glfwGetKey(m_Window, key.ID);
	}

	void InputCamera::Update(Entity& entity)
	{
		for (const auto& key : m_Keys)
			if (!key.Pressed)
				continue;
			else
				entity.Action(key.Action);
	}
}