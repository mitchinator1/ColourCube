#ifndef STATE_GAME_H
#define STATE_GAME_H
#include "StateBase.h"
#include <memory>

namespace Camera { class CameraBase; }
namespace Renderer { class RendererMaster; }
namespace Text { class FontType; }
namespace UI { class UIText; }
class Entity;
class Level;

namespace State
{
	class StateGame : public State::StateBase
	{
	private:
		Level* m_Level;
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::unique_ptr<Renderer::RendererMaster> m_Renderer;
		std::shared_ptr<Text::FontType> m_Font;
		std::vector<UI::UIText*> m_Texts;

		std::vector<Entity*> m_Entities;

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