#include "InputKeyboard.h"
#include "../Display.h"
#include "GLFW/glfw3.h"
#include "../Utility/FileProgram.h"

namespace Input
{
	InputKeyboard::InputKeyboard(std::shared_ptr<Display>& display, const std::string& filename)
		: InputBase(display)
	{
		LoadKeyCodes(filename);
	}

	InputKeyboard::~InputKeyboard()
	{

	}

	const std::string InputKeyboard::GetPressedKey()
	{
		bool capital = false;
		if (glfwGetKey(m_Display->Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(m_Display->Window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			capital = true;
		}
		
		for (auto& key : m_Keys)
		{
			if (glfwGetKey(m_Display->Window, key.code) == GLFW_PRESS)
			{
				if (!key.pressed)
				{
					key.pressed = true;
					if (capital)
					{
						char c = key.value[0];
						c = toupper(c);
						return std::string(1, c);
					}
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
		Utility::FileProgram file("Resources/Data/" + filename + ".data");
		file.LoadFile();

		for (auto& pair : file.GetValues())
		{
			m_Keys.emplace_back(Key{ std::stoi(pair.first), pair.second });
		}
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