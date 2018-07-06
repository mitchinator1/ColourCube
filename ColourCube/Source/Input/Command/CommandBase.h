#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H
#include <iostream>
#include "../../Entity.h"

namespace Command
{
	class CommandBase
	{
	public:
		unsigned int ID;

	public:
		CommandBase(unsigned int id) : ID(id) {}
		virtual ~CommandBase() {}
		virtual void Execute(Entity& entity) {}
	};

	class MoveUpCommand : public CommandBase
	{
	public:
		MoveUpCommand(unsigned int id) : CommandBase(id) {}
		void Execute(Entity& entity)
		{
			entity.GetPosition().y += 0.01f;
		}
	};

	class MoveDownCommand : public CommandBase
	{
	public:
		MoveDownCommand(unsigned int id) : CommandBase(id) {}
		void Execute(Entity& entity)
		{
			entity.GetPosition().y -= 0.01f;
		}
	};

	class MoveRightCommand : public CommandBase
	{
	public:
		MoveRightCommand(unsigned int id) : CommandBase(id) {}
		void Execute(Entity& entity)
		{
			entity.GetPosition().x += 0.01f;
		}
	};

	class MoveLeftCommand : public CommandBase
	{
	public:
		MoveLeftCommand(unsigned int id) : CommandBase(id) {}
		void Execute(Entity& entity)
		{
			entity.GetPosition().x -= 0.01f;
		}
	};

	class MoveForwardCommand : public CommandBase
	{
	public:
		MoveForwardCommand(unsigned int id) : CommandBase(id) {}
		void Execute(Entity& entity)
		{
			entity.GetModelMatrix()[1][1] += 0.5f;
			entity.GetPosition().z -= 0.01f;
		}
	};

	class MoveBackwardCommand : public CommandBase
	{
	public:
		MoveBackwardCommand(unsigned int id) : CommandBase(id) {}
		void Execute(Entity& entity)
		{
			entity.GetPosition().z += 0.01f;
		}
	};
}

#endif