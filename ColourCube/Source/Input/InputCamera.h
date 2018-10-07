#ifndef INPUT_CAMERA_H
#define INPUT_CAMERA_H
#include "InputKeyboard.h"
#include "Command/CommandBase.h"

namespace Input
{
	class InputCamera : public Input::InputKeyboard
	{
	private:
		float m_Speed = 1.0f;
		std::unique_ptr<Command::CommandBase> m_UpCommand;
		std::unique_ptr<Command::CommandBase> m_DownCommand;
		std::unique_ptr<Command::CommandBase> m_RightCommand;
		std::unique_ptr<Command::CommandBase> m_LeftCommand;
		std::unique_ptr<Command::CommandBase> m_ForwardCommand;
		std::unique_ptr<Command::CommandBase> m_BackwardCommand;

	public:
		InputCamera(std::shared_ptr<Display>& display);
		~InputCamera();

		void HandleEvents(Entity::EntityBase& entity);

	private:
		void LoadKeyBindings();
		
	};
}

#endif