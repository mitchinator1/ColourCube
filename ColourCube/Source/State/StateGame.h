#ifndef STATE_GAME_H
#define STATE_GAME_H
#include <memory>
#include "StateBase.h"

namespace Camera	{ class CameraBase; }
namespace Renderer	{ class RendererMaster; }
namespace UI		{ class UIMaster; }
class Level;

namespace State
{
	class StateGame : public State::StateBase
	{
	private:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Renderer::RendererMaster> m_Renderer;
		std::unique_ptr<UI::UIMaster> m_UI;
		std::shared_ptr<Display> m_Display;
		std::unique_ptr<Level> m_Level;

	public:
		StateGame() noexcept;
		~StateGame();

		void Init(std::shared_ptr<Display> display) override;

		void Pause() override;
		void Resume() override;

		void HandleEvents(GameEngine* game) override;
		void Update(GameEngine* game)		override;
		void Render() const					override;
	};
}

#endif