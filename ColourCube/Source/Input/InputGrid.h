#ifndef INPUT_GRID_H
#define INPUT_GRID_H
#include <vector>
#include <memory>
#include "InputBase.h"

struct GLFWwindow;

namespace Input
{
	class InputGrid : public Input::InputBase
	{
	private:
		GLFWwindow* m_Window;
		std::vector<Key> m_Keys;

	public:
		InputGrid(GLFWwindow* window);
		~InputGrid();

		void HandleEvents(Entity& entity) override;
		void Update(Entity& entity) override;
	};
}

#endif