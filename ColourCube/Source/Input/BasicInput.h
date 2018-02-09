#pragma once
#include "GLFW/glfw3.h"
#include "../Entity.h"

enum class Command;

struct Key
{
	int ID;
	Command Action;
	bool Pressed = false;
	float Toggled = 0;
};

class BasicInput
{
public:
	BasicInput() {};
	virtual ~BasicInput() {};
	virtual void HandleEvents() = 0;
	virtual void Update(Entity& entity) = 0;
};