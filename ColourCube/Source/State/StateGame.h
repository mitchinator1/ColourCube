#ifndef STATE_GAME_H
#define STATE_GAME_H
#include <memory>
#include "StateBase.h"

namespace Camera	{ class CameraBase; }
namespace Renderer	{ class RendererMaster; }
namespace UI		{ class UIMaster; }
class Level;
class Entity;

namespace State
{
	class StateGame : public State::StateBase
	{
	private:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Renderer::RendererMaster> m_Renderer;
		std::unique_ptr<UI::UIMaster> m_UI;
		std::shared_ptr<Display> m_Display;

		Level* m_Level;
		std::vector<Entity*> m_Entities;

	public:
		StateGame();
		~StateGame();

		void Init(std::shared_ptr<Display> display) override;

		void Pause();
		void Resume();

		void HandleEvents(GameEngine* game) override;
		void Update(GameEngine* game)		override;
		void Render()						override;
	};
}

#endif