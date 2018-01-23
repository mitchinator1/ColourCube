#include "GameEngine.h"
#include "States/GameState.h"

#include "Shader.h"
#include "BasicCamera.h"
#include "CameraInput.h"

#include "GLM/glm.hpp"

int main()
{
	GameEngine game("Colour Cube");
	game.Init();
	game.ChangeState(GameState::GetInstance());
	
	while (game.Running())
	{
		game.HandleEvents();
		game.Update();
		game.Draw();
	}
	
	game.CleanUp();
	return 0;
	/*
	Grid grid;

	Shader shader;
	shader.Bind();

	CameraInput camInput;
	BasicCamera camera(&camInput);
	camera.Bind(window);

	shader.SetUniformMat4("u_Projection", camera.GetProjectionMatrix(displayWidth, displayHeight));
	shader.SetUniformMat4("u_View", camera.GetViewMatrix());
	shader.SetUniformMat4("u_Model", grid.GetModelMatrix());
	
	while (!glfwWindowShouldClose(window))
	{
		camera.Update();
		
		shader.Bind();
		shader.SetUniformMat4("u_View", camera.GetViewMatrix());

		renderer.Draw(grid);

		shader.Unbind();
	}
	*/
}
