#ifndef INPUT_KEYBOARD_H
#define INPUT_KEYBOARD_H
#include "InputBase.h"

namespace Input
{
	struct Key
	{
		int code;
		std::string value;
		bool pressed = false;
	};

	class InputKeyboard : public InputBase
	{
	private:
		std::vector<Key> m_Keys;
		std::unordered_map<std::string, std::string> m_KeyCodes;
		const std::string NO_KEY = "";

	public:
		InputKeyboard(std::shared_ptr<Display>& display, const std::string& filename = "Keys");
		~InputKeyboard();

		const std::string GetPressedKey();

	protected:
		bool IsPressed(int id);
		void LoadKeyCodes(const std::string& filename);
		int GetKeyCode(const std::string& name);
	};
}

#endif