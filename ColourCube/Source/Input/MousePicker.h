#ifndef MOUSE_PICKER_H
#define MOUSE_PICKER_H
#include "Mouse3D.h"

namespace Input
{
	class MousePicker : public Mouse3D
	{
	private:
		float m_RayRange = 40.0f;

	public:
		MousePicker(std::shared_ptr<Camera::CameraBase>& camera, std::shared_ptr<Display>& display);
		~MousePicker() {}

		void HandleEvents()			override;
		void Update(Level& level)	override;
		bool ToggleMode()			override;
		void CalculateTargets(std::vector<std::unique_ptr<Cube>>& cubes) override;

	private:
		void CubeIntersection(Level& level);

	};
}

#endif