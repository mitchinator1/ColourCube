#pragma once
#include "InputBase.h"
#include "MousePicker.h"
#include <vector>
#include <memory>

namespace Input
{
	class InputGrid : public Input::InputBase
	{
	private:
		GLFWwindow* m_Window;
		std::unique_ptr<MousePicker> m_MousePicker;
		std::vector<Key> m_Keys = {
			{ GLFW_KEY_E,	Command::CHANGE_COLOUR },
			{ GLFW_KEY_R,	Command::CHANGE_COLOUR_2 } // Test Command
		};

	public:
		InputGrid(GLFWwindow* window, std::unique_ptr<MousePicker> mousePicker);
		~InputGrid();

		void HandleEvents(Entity& entity) override;
		void Update(Entity& entity) override;
	};
}