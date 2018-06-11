#ifndef MOUSE_PICKER_H
#define MOUSE_PICKER_H
#include "MouseBase.h"

namespace Input
{
	class MousePicker : public MouseBase
	{
	private:
		unsigned int m_RecursiveCount = 250;
		float m_RayRange = 30.0f;

	public:
		MousePicker(std::shared_ptr<Camera::CameraBase>& camera, std::shared_ptr<Display>& display);
		~MousePicker() {}

		void HandleEvents()			override;
		void Update(Level& level)	override;
		bool ToggleMode()			override;

	private:
		void CubeIntersection(glm::vec3 ray, Level& level);

	};
}

#endif