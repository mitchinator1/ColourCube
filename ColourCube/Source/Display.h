#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct Display
{
	GLFWwindow* Window;
	std::string Title;
	float Width, Height;

	Display(const std::string& title, float width, float height)
		: Window(nullptr), Title(title), Width(width), Height(height)
	{
		
	}

	bool Init()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		Window = glfwCreateWindow((int)Width, (int)Height, Title.c_str(), NULL, NULL);
		if (!Window)
		{
			std::cout << "Window not created." << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(Window);
		return true;
	}
};

#endif