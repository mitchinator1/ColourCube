#include "CameraInput.h"

CameraInput::CameraInput(GLFWwindow* window)
	: m_Window(window)
{

}

CameraInput::~CameraInput()
{

}

void CameraInput::HandleEvents()
{
	for (auto& key : m_Keys)
		key.Pressed = glfwGetKey(m_Window, key.ID);
}

void CameraInput::Update(Entity& entity)
{
	for (const auto& key : m_Keys)
		if (!key.Pressed)
			continue;
		else
			entity.Action(key.Action);
}
