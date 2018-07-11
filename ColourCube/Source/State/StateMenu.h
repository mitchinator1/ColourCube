#ifndef STATE_MENU_H
#define STATE_MENU_H
#include "StateBase.h"

namespace State
{
	class StateMenu : public StateBase
	{
	public:
		StateMenu(std::shared_ptr<Display>& display);
		~StateMenu();
		
		void HandleEvents(GameEngine* game)			override;
		void Update(GameEngine* game)				override;
		void Render()						const	override;
	};
}

#endif