#pragma once
#include "StateBase.h"
#include "../Renderer.h"
#include "../Level.h"
#include "../Shader.h"
#include "../Camera/CameraBase.h"
#include "../Entity.h"

namespace State
{
	class StateGame : public State::StateBase
	{
	private:
		Level* m_Level;
		Camera::CameraBase* m_Camera;
		Renderer m_Renderer;
		Shader m_Shader;
		std::vector<Entity*> m_Entities;

	public:
		StateGame();
		~StateGame();

		void Init(GLFWwindow* window);

		void Pause();
		void Resume();

		void HandleEvents(GameEngine* game);
		void Update(GameEngine* game);
		void Draw(GameEngine* game);
	};
}
