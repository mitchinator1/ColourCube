#ifndef MOUSE_PICKER_H
#define MOUSE_PICKER_H
#include <memory>
#include "InputBase.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"

class Level;
namespace Camera { class CameraBase; }
struct Display;

namespace Input
{
	class MousePicker : public Input::InputBase
	{
	private:
		int m_RecursiveCount = 200;
		float m_RayRange = 50;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_CurrentPoint = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CurrentRay = { 0.0f, 0.0f, 0.0f };

		bool MouseButtonIsPressed = false;
		float Toggled = 0.0f;
		double mouseX = 0.0f;
		double mouseY = 0.0f;
		
		std::shared_ptr<Camera::CameraBase> m_Camera;
		std::shared_ptr<Display> m_Display;

	public:
		MousePicker(std::shared_ptr<Camera::CameraBase> camera, std::shared_ptr<Display> display);
		~MousePicker() {}

		void HandleEvents(Entity& entity) override;
		void Update(Entity& entity) override;

		inline glm::vec3& GetCurrentPoint() { return m_CurrentPoint; }
		inline glm::vec3& GetCurrentRay() { return m_CurrentRay; }


	private:
		void GetMouseInput();

		glm::vec3 CalculateMouseRay();
		glm::vec3 ToWorldCoords(glm::vec4 eyeCoords);
		glm::vec4 ToEyeCoords(glm::vec4 clipCoords);
		glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);

		glm::vec3 GetPointOnRay(glm::vec3 ray, float distance);
		glm::vec3 BinarySearch(int count, float start, float finish, glm::vec3 ray);
		bool IntersectionInRange(float start, float finish, glm::vec3& ray);
		bool IsBelowGrid(glm::vec3 testPoint);
	};
}

#endif