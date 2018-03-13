#include "GameEngine.h"
#include "State/StateGame.h"
//#include "State/StateMenu.h"

int main() 
{
	GameEngine* game = new GameEngine("Colour Cube", 1800, 1200);
	game->ChangeState(new State::StateGame());
	
	while (game->Running())
	{
		game->HandleEvents();
		game->Update();
		game->Draw();
	}

	delete game;
	return 0;
}
