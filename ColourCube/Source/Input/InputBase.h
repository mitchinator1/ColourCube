#ifndef INPUT_BASE_H
#define INPUT_BASE_H
#include <vector>
#include <memory>
#include "../Display.h"

//TODO: Change to Command Pattern
enum class Command
{
	FORWARD = 0,
	BACKWARD = 1,
	LEFT = 2,
	RIGHT = 3,
	UP = 4,
	DOWN = 5,
	CHANGE_COLOUR = 6,
	SAVE = 7
};

class Entity;

namespace Input
{
	struct Key
	{
		int ID;
		Command Action;
		bool Pressed = false;
		float Toggled = 0.0f;
	};

	class InputBase
	{
	protected:
		std::vector<Key> m_Keys;
		std::shared_ptr<Display> m_Display;

	public:
		InputBase(std::shared_ptr<Display>& display) : m_Display(display) {};
		virtual ~InputBase() {};

		virtual void HandleEvents(Entity& entity)
		{
			for (auto& key : m_Keys)
				key.Pressed = glfwGetKey(m_Display->Window, key.ID);
		};

		virtual void Update(Entity& entity) = 0;
	};
}

#endif