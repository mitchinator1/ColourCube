#ifndef STATE_MENU_H
#define STATE_MENU_H
#include <memory>
#include "StateBase.h"

namespace UI { class UIMaster; }
namespace Renderer { class RendererMaster; }

namespace State
{
	class StateMenu : public StateBase
	{
	private:
		std::unique_ptr<UI::UIMaster> m_UI;
		std::unique_ptr<Renderer::RendererMaster> m_Renderer;
		std::shared_ptr<Display> m_Display;

	public:
		StateMenu() noexcept;
		~StateMenu();

		void Init(std::shared_ptr<Display> display) override;

		void Pause() override;
		void Resume() override;

		void HandleEvents(GameEngine* game) override;
		void Update(GameEngine* game) override;
		void Render() const override;
	};
}

#endif