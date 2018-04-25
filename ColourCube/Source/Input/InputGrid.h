#ifndef INPUT_GRID_H
#define INPUT_GRID_H
#include <vector>
#include <memory>
#include "InputBase.h"
#include "GLFW/glfw3.h"

namespace Input
{
	class InputGrid : public Input::InputBase
	{
	private:
		GLFWwindow* m_Window;
		std::vector<Key> m_Keys = {
			{ GLFW_KEY_E,	Command::CHANGE_COLOUR },
			{ GLFW_KEY_R,	Command::SAVE } // Test Command
		};

	public:
		InputGrid(GLFWwindow* window);
		~InputGrid();

		void HandleEvents(Entity& entity) override;
		void Update(Entity& entity) override;
	};
}

#endif