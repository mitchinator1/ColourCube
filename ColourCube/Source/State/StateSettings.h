#ifndef STATE_SETTINGS_H
#define STATE_SETTINGS_H
#include <memory>
#include "StateBase.h"

namespace UI { class UIMaster; }
namespace Renderer { class RendererMaster; }

namespace State
{

	class StateSettings : public StateBase
	{
	private:
		std::unique_ptr<UI::UIMaster> m_UI;
		std::unique_ptr<Renderer::RendererMaster> m_Renderer;
		std::shared_ptr<Display> m_Display;

	public:
		StateSettings() noexcept;
		~StateSettings();

		void Init(std::shared_ptr<Display> display) override;

		void Pause() override;
		void Resume() override;

		void HandleEvents(GameEngine* game) override;
		void Update(GameEngine* game) override;
		void Render() const override;
	};
}

#endif