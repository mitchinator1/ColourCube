#pragma once
#include "GLM/glm.hpp"
#include "../Camera/CameraBasic.h"

class Grid;

namespace Input
{
	class MousePicker
	{
	private:
		int m_RecursiveCount = 100;
		float m_RayRange = 50;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_CurrentGridPoint;
		glm::vec3 m_CurrentRay = { 0.0f, 0.0f, 0.0f };

		Camera::Basic* m_Camera;
		GLFWwindow* m_Window;

	public:
		MousePicker(Camera::Basic* camera, GLFWwindow* window);
		void Update(Entity& entity);
		glm::vec3 GetCurrentGridPoint();
		glm::vec3 GetCurrentRay();

	private:
		glm::vec3 CalculateMouseRay();

		glm::vec3 GetPointOnRay(glm::vec3 ray, float distance);
		glm::vec3 BinarySearch(int count, float start, float finish, glm::vec3 ray);
		bool IntersectionInRange(float start, float finish, glm::vec3 ray);
		bool IsBelowGrid(glm::vec3 testPoint);
	};
}