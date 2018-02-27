#include "GameEngine.h"
#include "States/GameState.h"

int main() 
{
	GameEngine* game = new GameEngine("Colour Cube", 1800, 1200);
	game->ChangeState(new GameState());
	
	while (game->Running())
	{
		game->HandleEvents();
		game->Update();
		game->Draw();
	}

	delete game;
	return 0;
}
