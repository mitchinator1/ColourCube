#include "GameEngine.h"
#include "State/StateGame.h"

int main() 
{
	GameEngine* game = new GameEngine("Colour Cube", 1800, 1200);
	game->ChangeState(new State::Game());
	
	while (game->Running())
	{
		game->HandleEvents();
		game->Update();
		game->Draw();
	}

	delete game;
	return 0;
}
