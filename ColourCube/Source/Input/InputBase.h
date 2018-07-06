#ifndef INPUT_BASE_H
#define INPUT_BASE_H
#include <vector>
#include <memory>
#include "Command/CommandBase.h"

//TODO: Change to Command Pattern
//enum class Command
//{
//	FORWARD = 0,
//	BACKWARD = 1,
//	LEFT = 2,
//	RIGHT = 3,
//	UP = 4,
//	DOWN = 5,
//	CHANGE_COLOUR = 6,
//	SAVE = 7
//};

class Entity;
struct Display;
namespace Command { class CommandBase; }

namespace Input
{
	struct Key
	{
		int ID;
		//Command Action;
		std::unique_ptr<Command::CommandBase> command;
		bool Pressed = false;
		float Toggled = 0.0f;
	};

	class InputBase
	{
	protected:
		std::vector<Key> m_Keys;
		std::shared_ptr<Display> m_Display;

	public:
		InputBase(std::shared_ptr<Display>& display);
		virtual ~InputBase();

		virtual void HandleEvents(Entity& entity);
		virtual void Update(Entity& entity);

	protected:
		bool IsPressed(unsigned int id);
	};
}

#endif