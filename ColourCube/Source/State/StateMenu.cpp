#include "StateMenu.h"
#include <iostream>

State::StateMenu::StateMenu()
{
	std::cout << "Menu Constructed" << std::endl;
}

State::StateMenu::~StateMenu()
{
}

void State::StateMenu::Init(GLFWwindow* window)
{
}

void State::StateMenu::Pause()
{
}

void State::StateMenu::Resume()
{
}

void State::StateMenu::HandleEvents(GameEngine* game)
{
}

void State::StateMenu::Update(GameEngine* game)
{
}

void State::StateMenu::Draw(GameEngine* game)
{
}
