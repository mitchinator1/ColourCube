#include "GameEngine.h"
#include <memory>
#include "State/StateMenu.h"

int main() 
{
	std::unique_ptr<GameEngine> game = std::make_unique<GameEngine>("Colour Cube", 1800.0f, 1200.0f);
	game->ChangeState(std::make_unique<State::StateMenu>());
	
	while (game->Running())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	return 0;
}
