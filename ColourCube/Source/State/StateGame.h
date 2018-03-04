#pragma once
#include "StateBase.h"
#include "../Renderer.h"
#include "../Grid.h"
#include "../Shader.h"
#include "../Camera/CameraBase.h"
#include "../Entity.h"

namespace State
{
	class Game : public State::StateBase
	{
	private:
		Grid* m_Grid;
		Camera::CameraBase* m_Camera;
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
