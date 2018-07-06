#ifndef INPUT_CAMERA_H
#define INPUT_CAMERA_H
#include "InputBase.h"
#include "Command/CommandBase.h"

namespace Input
{
	class InputCamera : public Input::InputBase
	{
	private:
		float m_Speed = 1.0f;

	public:
		InputCamera(std::shared_ptr<Display>& display);
		~InputCamera();

		void HandleEvents(Entity& entity);

	private:
		std::unique_ptr<Command::CommandBase> m_UpCommand;
		std::unique_ptr<Command::CommandBase> m_DownCommand;
		std::unique_ptr<Command::CommandBase> m_RightCommand;
		std::unique_ptr<Command::CommandBase> m_LeftCommand;
		std::unique_ptr<Command::CommandBase> m_ForwardCommand;
		std::unique_ptr<Command::CommandBase> m_BackwardCommand;
		
	};
}

#endif