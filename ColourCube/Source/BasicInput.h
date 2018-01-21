#pragma once
#include "GLFW/glfw3.h"
#include <vector>
#include "Entity.h"

struct Key
{
	int ID;
	bool Pressed = false;
	float Toggled = 0;
};

class BasicInput
{
public:
	virtual void Update(Entity& entity) = 0;
	virtual Key& GetKey(int key) = 0;
	virtual void Bind(GLFWwindow* window) = 0;

private:
	std::vector<Key> m_Keys;
};