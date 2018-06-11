#ifndef INPUT_CAMERA_H
#define INPUT_CAMERA_H
#include "InputBase.h"
#include "GLFW/glfw3.h"

namespace Input
{
	class InputCamera : public Input::InputBase
	{
	private:
		float m_Speed = 1.0f;

	public:
		InputCamera(std::shared_ptr<Display>& display);
		~InputCamera();

		void Update(Entity& entity)		override;

	};
}

#endif