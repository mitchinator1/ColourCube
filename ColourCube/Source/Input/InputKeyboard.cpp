#include "InputKeyboard.h"
#include <fstream>
#include <sstream>
#include "../Display.h"
#include "GLFW/glfw3.h"

namespace Input
{
	InputKeyboard::InputKeyboard(std::shared_ptr<Display>& display, const std::string& filename)
		: InputBase(display)
	{
		//TODO: Use Meta file for keys
		LoadKeyCodes(filename);
	}

	InputKeyboard::~InputKeyboard()
	{

	}

	const std::string& InputKeyboard::GetPressedKey()
	{
		for (auto& key : m_Keys)
		{
			if (glfwGetKey(m_Display->Window, key.code) == GLFW_PRESS)
			{
				if (!key.pressed)
				{
					key.pressed = true;
					return key.value;
				}
			}
			else
			{
				if (key.pressed)
				{
					key.pressed = false;
				}
			}
		}

		return NO_KEY;
	}

	bool InputKeyboard::IsPressed(int id)
	{
		return glfwGetKey(m_Display->Window, id);
	}

	void InputKeyboard::LoadKeyCodes(const std::string& filename)
	{
		std::string filepath = "Resources/Data/" + filename + ".data";
		std::ifstream file(filepath);

		std::string line;
		while (std::getline(file, line, '\n'))
		{
			std::istringstream pair(line);
			std::string name, value;

			std::getline(pair, name, '=');
			int code = 0;
			pair >> code;
			m_Keys.emplace_back(Key{ code, name });
		}
		file.close();
	}

	int InputKeyboard::GetKeyCode(const std::string& name)
	{
		for (auto& key : m_Keys)
		{
			if (key.value == name)
			{
				return key.code;
			}
		}

		return 0;
	}

}