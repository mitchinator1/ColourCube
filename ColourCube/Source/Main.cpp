#include "GameEngine.h"
#include "States/GameState.h"

int main() 
{
	GameEngine game("Colour Cube", 1800, 1200);
	game.Init();
	game.ChangeState(GameState::GetInstance());
	
	while (game.Running())
	{
		game.HandleEvents();
		game.Update();
		game.Draw();
	}
	
	game.CleanUp();
	return 0;
}
