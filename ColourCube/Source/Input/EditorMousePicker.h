#ifndef EDITOR_MOUSE_PICKER_H
#define EDITOR_MOUSE_PICKER_H
#include "MouseBase.h"

namespace Input
{
	class EditorMousePicker : public MouseBase
	{
	private:
		unsigned int m_RecursiveCount = 250;
		float m_RayRange = 40.0f;
		bool m_AddCubeToggled = true;

	public:
		EditorMousePicker(std::shared_ptr<Camera::CameraBase>& camera, std::shared_ptr<Display>& display);
		~EditorMousePicker() {}

		void HandleEvents()			override;
		void Update(Level& level)	override;
		bool ToggleMode()			override;
		
	private:
		void CubeIntersection(glm::vec3 ray, Level& level);
		void AddCube(glm::vec3 hitPoint, glm::vec3 target, Level& level);

	};
}

#endif