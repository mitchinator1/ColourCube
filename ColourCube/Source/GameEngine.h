#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <vector>
#include <memory>
#include <string>

namespace State { class StateBase; }
struct Display;

class GameEngine
{
private:
	bool m_Running;
	std::shared_ptr<Display> m_Display;
	std::vector<std::unique_ptr<State::StateBase>> m_States;

public:
	GameEngine(const std::string& title, float width, float height);
	~GameEngine();

	bool Init();

	void ChangeState(std::unique_ptr<State::StateBase> state);
	void PushState(std::unique_ptr<State::StateBase> state);
	void PopState();

	void HandleEvents();
	void Update();
	void Render();

	void Quit();

	inline bool Running()		const	{ return m_Running; }
	inline auto& GetDisplay()			{ return m_Display; }
};

#endif