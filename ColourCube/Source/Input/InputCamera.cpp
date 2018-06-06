#include "InputCamera.h"
#include "../Entity.h"

namespace Input
{
	InputCamera::InputCamera(std::shared_ptr<Display>& display)
		: InputBase(display)
	{

	}

	InputCamera::~InputCamera()
	{
		
	}

	void InputCamera::HandleEvents(Entity& entity)
	{
		for (auto& key : m_Keys)
			key.Pressed = glfwGetKey(m_Display->Window, key.ID);
	}

	void InputCamera::Update(Entity& entity)
	{
		for (const auto& key : m_Keys)
			if (!key.Pressed)
				continue;
			else
				entity.Action(key.Action);
	}
}