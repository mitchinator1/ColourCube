#ifndef STATE_GAME_H
#define STATE_GAME_H
#include "StateBase.h"
#include <memory>
#include "../UI/UIMaster.h"

class Level;
namespace Camera { class CameraBase; }
namespace Renderer { class RendererMaster; }
class Entity;

namespace State
{
	class StateGame : public State::StateBase
	{
	private:
		Level* m_Level;
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Renderer::RendererMaster> m_Renderer;

		std::vector<Entity*> m_Entities;
		UI::UIMaster m_UI;

	public:
		StateGame();
		~StateGame();

		void Init(GLFWwindow* window);

		void Pause();
		void Resume();

		void HandleEvents(GameEngine* game) override;
		void Update(GameEngine* game) override;
		void Render() override;
	};
}

#endif