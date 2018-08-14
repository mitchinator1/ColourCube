#include "InputBase.h"
#include <fstream>
#include <sstream>
#include "../Display.h"

namespace Input
{
	InputBase::InputBase(std::shared_ptr<Display>& display)
		: m_Display(display)
	{
		LoadKeyCodes("Settings");
	}

	InputBase::~InputBase()
	{

	}

	bool InputBase::IsPressed(int id)
	{
		return glfwGetKey(m_Display->Window, id);
	}

	void InputBase::LoadKeyCodes(const std::string& filename)
	{
		std::string filepath = "Resources/Data/" + filename + ".data";
		std::ifstream file(filepath);

		std::string line;
		while (std::getline(file, line, '\n'))
		{
			std::istringstream pair(line);
			std::string name, value;

			std::getline(pair, name, '=');
			std::getline(pair, value, '\n');

			m_KeyCodes.insert({ name, value });
		}
		file.close();
	}

	int InputBase::GetKeyCode(const std::string& name)
	{
		if (m_KeyCodes.find(name) != m_KeyCodes.end())
			return std::stoi(m_KeyCodes[name]);

		return 0;
	}

	const char* InputBase::GetKeyName(const unsigned int code)
	{
		auto name = glfwGetKeyName(code, 0);
		if (!name)
			return "Invalid";
		return name;
	}

}