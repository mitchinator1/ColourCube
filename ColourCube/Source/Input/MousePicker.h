#ifndef MOUSE_PICKER_H
#define MOUSE_PICKER_H
#include <memory>
#include <vector>
#include "MouseBase.h"

class Level;
namespace Camera { class CameraBase; }
struct Display;

namespace Input
{
	class MousePicker : public MouseBase
	{
	private:
		unsigned int m_RecursiveCount = 250;
		float m_RayRange = 30.0f;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::shared_ptr<Display> m_Display;

	public:
		MousePicker(std::shared_ptr<Camera::CameraBase> camera, std::shared_ptr<Display> display);
		~MousePicker() {}

		void HandleEvents()			override;
		void Update(Level& level)	override;
		bool ToggleMode()			override;

	private:
		void GetMouseInput();

		glm::vec3 CalculateMouseRay();
		glm::vec3 ToWorldCoords(glm::vec4 eyeCoords);
		glm::vec4 ToEyeCoords(glm::vec4 clipCoords);
		glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);

		void CubeIntersection(glm::vec3 ray, Level& level);
	};
}

#endif