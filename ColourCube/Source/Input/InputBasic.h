#pragma once
#include "GLFW/glfw3.h"
#include "../Entity.h"

enum class Command;

namespace Input
{
	struct Key
	{
		int ID;
		Command Action;
		bool Pressed = false;
		float Toggled = 0.0f;
	};

	class Basic
	{
	public:
		Basic() {};
		virtual ~Basic() {};
		virtual void HandleEvents() = 0;
		virtual void Update(Entity& entity) = 0;
	};
}