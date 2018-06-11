#ifndef INPUT_GRID_H
#define INPUT_GRID_H
#include "InputBase.h"

struct GLFWwindow;

namespace Input
{
	class InputGrid : public Input::InputBase
	{
	public:
		InputGrid(std::shared_ptr<Display>& display);
		~InputGrid();

		void Update(Entity& entity)		override;
	};
}

#endif