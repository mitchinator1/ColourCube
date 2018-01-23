#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Shader.h"
#include "BasicCamera.h"
#include "Grid.h"

#include "GLM/glm.hpp"

#include "Renderer.h"

#include "CameraInput.h"

GLFWwindow* CreateWindow(int width, int height);

int main()
{
	/*
	GameEngine game("Colour Cube");
	game.Init();
	game.PushState(GameState gameState);
	*/
	int displayWidth = 1600;
	int displayHeight = 1200;
	if (!glfwInit())
		return -1;

	GLFWwindow* window = CreateWindow(displayWidth, displayHeight);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;

	glEnable(GL_CULL_FACE);

	Grid grid;

	Shader shader;
	shader.Bind();

	CameraInput camInput;
	BasicCamera camera(&camInput);
	camera.Bind(window);

	shader.SetUniformMat4("u_Projection", camera.GetProjectionMatrix(displayWidth, displayHeight));
	shader.SetUniformMat4("u_View", camera.GetViewMatrix());
	shader.SetUniformMat4("u_Model", grid.GetModelMatrix());

	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		camera.Update();
		
		shader.Bind();
		shader.SetUniformMat4("u_View", camera.GetViewMatrix());

		renderer.Draw(grid);

		shader.Unbind();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}

GLFWwindow* CreateWindow(int width, int height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Colour Cube", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	return window;
}