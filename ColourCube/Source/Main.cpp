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

int main()
{
	int displayWidth = 1600;
	int displayHeight = 1200;
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(displayWidth, displayHeight, "Colour Cube", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;

	float vertices[] = {
		-1.0f, -1.0f,  0.0f,		1.0f, 0.5f, 0.0f,
		 1.0f, -1.0f,  0.0f,		1.0f, 0.5f, 1.0f,
		 1.0f,  1.0f,  0.0f,	 	1.0f, 0.5f, 1.0f,
		-1.0f,  1.0f,  0.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f,  0.0f,		1.0f, 0.5f, 0.0f,
		 1.0f,  1.0f,  0.0f,		0.4f, 0.5f, 0.6f,
		 1.0f,  1.0f, -1.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f, -1.0f,		1.0f, 0.5f, 0.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4
	};

	VertexArray va;
	VertexBuffer vb(vertices, 8 * 6 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	Shader shader;
	shader.Bind();

	BasicCamera camera(0.0f, 0.0f, 5.0f);
	camera.Bind(window);

	shader.SetUniformMat4("u_Projection", camera.GetProjectionMatrix(displayWidth, displayHeight));
	shader.SetUniformMat4("u_View", camera.GetViewMatrix());

	glm::mat4 modelMatrix;
	shader.SetUniformMat4("u_Model", modelMatrix);

	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		camera.GetInput();
		
		shader.Bind();
		shader.SetUniformMat4("u_View", camera.GetViewMatrix());

		renderer.Draw(va, ib);

		shader.Unbind();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
