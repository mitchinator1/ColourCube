#ifndef STATE_MENU_H
#define STATE_MENU_H
#include <memory>
#include "StateBase.h"

namespace Renderer { class RendererMaster; }
namespace Camera { class CameraBase; }
namespace UI { class UIMaster; }

namespace State
{
	class StateMenu : public State::StateBase
	{
	private:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Renderer::RendererMaster> m_Renderer;
		std::unique_ptr<UI::UIMaster> m_UI;

	public:
		StateMenu();
		~StateMenu();

		void Init(GLFWwindow* window) override;

		void Pause() override;
		void Resume() override;

		void HandleEvents(GameEngine* game) override;
		void Update(GameEngine* game) override;
		void Render() override;
	};
}

#endif