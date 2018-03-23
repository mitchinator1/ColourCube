#include "GameEngine.h"
#include "State/StateGame.h"
#include <memory>

int main() 
{
	GameEngine* game = new GameEngine("Colour Cube", 1800, 1200);
	game->ChangeState(std::make_unique<State::StateGame>());
	
	while (game->Running())
	{
		game->HandleEvents();
		game->Update();
		game->Draw();
	}

	delete game;
	return 0;
}
