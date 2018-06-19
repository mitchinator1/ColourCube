#ifndef INPUT_CAMERA_H
#define INPUT_CAMERA_H
#include "InputBase.h"

namespace Input
{
	class InputCamera : public Input::InputBase
	{
	private:
		float m_Speed = 1.0f;

	public:
		InputCamera(std::shared_ptr<Display>& display);
		~InputCamera();
		
	};
}

#endif