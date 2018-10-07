#include "InputBase.h"
#include <fstream>
#include <sstream>
#include "../Display.h"

namespace Input
{
	InputBase::InputBase(std::shared_ptr<Display>& display)
		: m_Display(display)
	{
	}

	InputBase::~InputBase()
	{

	}

}