#include "InputBase.h"
#include "../Entity.h"
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

	void InputBase::HandleEvents(Entity& entity)
	{
		for (auto& key : m_Keys)
		{
			key.Pressed = glfwGetKey(m_Display->Window, key.ID);
		}
	};

	void InputBase::Update(Entity& entity)
	{
		for (const auto& key : m_Keys)
		{
			if (!key.Pressed)
			{
				continue;
			}
			else
			{
				//entity.Action(key.Action);
			}
		}
	}

	bool InputBase::IsPressed(unsigned int id)
	{
		return glfwGetKey(m_Display->Window, id);
	}

}