#ifndef INPUT_CAMERA_H
#define INPUT_CAMERA_H
#include <vector>
#include <memory>
#include "InputBase.h"
#include "GLFW/glfw3.h"

namespace Input
{
	class InputCamera : public Input::InputBase
	{
	private:
		std::vector<Key> m_Keys = {
		{ GLFW_KEY_W,			Command::FORWARD },
		{ GLFW_KEY_S,			Command::BACKWARD },
		{ GLFW_KEY_A,			Command::LEFT },
		{ GLFW_KEY_D,			Command::RIGHT },
		{ GLFW_KEY_SPACE,		Command::UP },
		{ GLFW_KEY_LEFT_SHIFT,	Command::DOWN }
		};
		float m_Speed = 1.0f;

	public:
		InputCamera(std::shared_ptr<Display>& display);
		~InputCamera();

		void HandleEvents(Entity& entity)	override;
		void Update(Entity& entity)			override;

	};
}

#endif