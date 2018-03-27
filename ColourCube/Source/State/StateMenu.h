#ifndef STATE_MENU_H
#define STATE_MENU_H
#include "StateBase.h"
#include "../Renderer/RendererMaster.h"
#include "../Camera/CameraBase.h"
#include "../UI/UIButton.h"
#include "../UI/UIMaster.h"

#include <memory>

namespace State
{
	class StateMenu : public State::StateBase
	{
	private:
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Renderer::RendererMaster> m_Renderer;

		std::shared_ptr<Text::FontType> m_Font;
		std::vector<Text::GUIText*> m_Texts;

		std::vector<UI::UIButton> m_Buttons;
		UI::UIMaster m_UIMaster;

	public:
		StateMenu();
		~StateMenu();

		void Init(GLFWwindow* window);

		void Pause();
		void Resume();

		void HandleEvents(GameEngine* game);
		void Update(GameEngine* game);
		void Render() override;
	};
}

#endif