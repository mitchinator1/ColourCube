#pragma once
#include "InputBasic.h"
#include "MousePicker.h"
#include <vector>

namespace Input
{
	class Grid : public Basic
	{
	private:
		GLFWwindow* m_Window;
		MousePicker* m_MousePicker;
		std::vector<Key> m_Keys = {
			{ GLFW_KEY_E,	Command::CHANGE_COLOUR },
			{ GLFW_KEY_R,	Command::CHANGE_COLOUR_2 } // Test Command
		};

	public:
		Grid(GLFWwindow* window, MousePicker* mousePicker);
		~Grid() {}

		void HandleEvents();
		void Update(Entity& entity);
	};
}