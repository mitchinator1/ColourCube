#ifndef INPUT_BASE_H
#define INPUT_BASE_H
#include "../Entity.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

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
	CHANGE_COLOUR_2 = 7 // Test Command
};

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
	public:
		InputBase() {};
		virtual ~InputBase() {};
		virtual void HandleEvents(Entity& entity) = 0;
		virtual void Update(Entity& entity) = 0;
	};
}

#endif