#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BasicCamera.h"

#include "GLM/glm.hpp"

#include "Renderer.h"

#include "CameraInput.h"

GLFWwindow* CreateWindow(int width, int height);

int main()
{
	int displayWidth = 1600;
	int displayHeight = 1200;
	if (!glfwInit())
		return -1;

	GLFWwindow* window = CreateWindow(displayWidth, displayHeight);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;

	glEnable(GL_CULL_FACE);

	float vertices[] = {
		-1.0f, -1.0f,  0.0f,		1.0f, 0.5f, 0.0f,
		 1.0f, -1.0f,  0.0f,		1.0f, 0.5f, 1.0f,
		 1.0f,  1.0f,  0.0f,	 	1.0f, 0.5f, 1.0f,
		-1.0f,  1.0f,  0.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f,  0.0f,		1.0f, 0.5f, 0.0f,
		 1.0f,  1.0f,  0.0f,		0.4f, 0.5f, 0.6f,
		 1.0f,  1.0f, -1.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f, -1.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,	1.0f, -1.0f,		1.0f, 0.8f, 0.8f,
		-1.0f, -1.0f, -1.0f,		1.0f, 0.4f, 0.7f,
		-1.0f, -1.0f,  0.0f,		0.8f, 0.8f, 0.6f,
		-1.0f,	1.0f,  0.0f,		0.7f, 0.7f, 0.2f
	};

	unsigned int indices[] = {
		0,  1,  2,
		2,  3,  0,
		4,  5,  6,
		6,  7,  4,
		8,  9,  10,
		10, 11,  8
	};

	VertexArray va;
	VertexBuffer vb(vertices, 12 * 6 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 18);

	Shader shader;
	shader.Bind();

	CameraInput camInput;
	BasicCamera camera(&camInput);
	camera.Bind(window);

	shader.SetUniformMat4("u_Projection", camera.GetProjectionMatrix(displayWidth, displayHeight));
	shader.SetUniformMat4("u_View", camera.GetViewMatrix());

	glm::mat4 modelMatrix;
	shader.SetUniformMat4("u_Model", modelMatrix);

	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{
		camera.Update();
		
		shader.Bind();
		shader.SetUniformMat4("u_View", camera.GetViewMatrix());

		glClear(GL_COLOR_BUFFER_BIT);
		renderer.Draw(va, ib);

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