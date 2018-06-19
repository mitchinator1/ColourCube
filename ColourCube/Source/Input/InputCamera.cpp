#include "InputCamera.h"
#include "../Entity.h"
#include "GLFW/glfw3.h"

namespace Input
{
	InputCamera::InputCamera(std::shared_ptr<Display>& display)
		: InputBase(display)
	{
		m_Keys = {
			{ GLFW_KEY_W,			Command::FORWARD },
			{ GLFW_KEY_S,			Command::BACKWARD },
			{ GLFW_KEY_A,			Command::LEFT },
			{ GLFW_KEY_D,			Command::RIGHT },
			{ GLFW_KEY_SPACE,		Command::UP },
			{ GLFW_KEY_LEFT_SHIFT,	Command::DOWN }
		};
	}

	InputCamera::~InputCamera()
	{
		
	}

}