#include "InputCamera.h"
#include "../Entity.h"
#include "../Display.h"
#include "GLFW/glfw3.h"

namespace Input
{
	InputCamera::InputCamera(std::shared_ptr<Display>& display)
		: InputBase(display)
	{
		/*m_Keys = {
			{ GLFW_KEY_W,			Command::FORWARD },
			{ GLFW_KEY_S,			Command::BACKWARD },
			{ GLFW_KEY_A,			Command::LEFT },
			{ GLFW_KEY_D,			Command::RIGHT },
			{ GLFW_KEY_SPACE,		Command::UP },
			{ GLFW_KEY_LEFT_SHIFT,	Command::DOWN }
		};*/
		m_UpCommand = std::make_unique<Command::MoveUpCommand>(GLFW_KEY_SPACE);
		m_DownCommand = std::make_unique<Command::MoveDownCommand>(GLFW_KEY_LEFT_SHIFT);
		m_RightCommand = std::make_unique<Command::MoveRightCommand>(GLFW_KEY_D);
		m_LeftCommand = std::make_unique<Command::MoveLeftCommand>(GLFW_KEY_A);
		m_ForwardCommand = std::make_unique<Command::MoveForwardCommand>(GLFW_KEY_W);
		m_BackwardCommand = std::make_unique<Command::MoveBackwardCommand>(GLFW_KEY_S);
	}

	InputCamera::~InputCamera()
	{
		
	}

	void InputCamera::HandleEvents(Entity& entity)
	{
		if (IsPressed(m_UpCommand->ID))
			m_UpCommand->Execute(entity);
		if (IsPressed(m_DownCommand->ID))
			m_DownCommand->Execute(entity);
		if (IsPressed(m_RightCommand->ID))
			m_RightCommand->Execute(entity);
		if (IsPressed(m_LeftCommand->ID))
			m_LeftCommand->Execute(entity);
		if (IsPressed(m_ForwardCommand->ID))
			m_ForwardCommand->Execute(entity);
		if (IsPressed(m_BackwardCommand->ID))
			m_BackwardCommand->Execute(entity);
	}

}