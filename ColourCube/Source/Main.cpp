#include "GameEngine.h"
//#include "State/StateGame.h"
#include "State/StateMenu.h"
#include <memory>

int main() 
{
	GameEngine* game = new GameEngine("Colour Cube", 1800, 1200);
	//game->ChangeState(std::make_unique<State::StateGame>());
	game->ChangeState(std::make_unique<State::StateMenu>());
	
	while (game->Running())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	//delete game;
	return 0;
}
