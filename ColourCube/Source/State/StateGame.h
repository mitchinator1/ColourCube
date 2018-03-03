#pragma once
#include "StateBasic.h"
#include "../Renderer.h"
#include "../Grid.h"
#include "../Shader.h"
#include "../Camera/CameraBasic.h"
#include "../Entity.h"

namespace State
{
	class Game : public Basic
	{
	private:
		Grid* m_Grid;
		Camera::Basic* m_Camera;
		//Input::MousePicker* m_MousePicker;
		Renderer m_Renderer;
		Shader m_Shader;
		std::vector<Entity*> m_Entities;

	public:
		Game();
		~Game();

		void Init(GLFWwindow* window);

		void Pause();
		void Resume();

		void HandleEvents(GameEngine* game);
		void Update(GameEngine* game);
		void Draw(GameEngine* game);
	};
}
