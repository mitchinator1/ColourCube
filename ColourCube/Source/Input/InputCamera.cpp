#include "InputCamera.h"
#include "../Entity/EntityBase.h"
#include "../Display.h"

namespace Input
{
	InputCamera::InputCamera(std::shared_ptr<Display>& display)
		: InputKeyboard(display, "Settings")
	{
		LoadKeyBindings();
	}

	InputCamera::~InputCamera()
	{
		
	}

	void InputCamera::HandleEvents(Entity::EntityBase& entity)
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

	void InputCamera::LoadKeyBindings()
	{
		m_UpCommand = std::make_unique<Command::MoveUpCommand>(GetKeyCode("Up"));
		m_DownCommand = std::make_unique<Command::MoveDownCommand>(GetKeyCode("Down"));
		m_RightCommand = std::make_unique<Command::MoveRightCommand>(GetKeyCode("Right"));
		m_LeftCommand = std::make_unique<Command::MoveLeftCommand>(GetKeyCode("Left"));
		m_ForwardCommand = std::make_unique<Command::MoveForwardCommand>(GetKeyCode("Forward"));
		m_BackwardCommand = std::make_unique<Command::MoveBackwardCommand>(GetKeyCode("Backward"));
	}

}