#include "MousePicker.h"
#include "GLM/gtc/matrix_transform.hpp"
#include <iostream>

namespace Input
{
	MousePicker::MousePicker(Camera::Basic* camera, GLFWwindow* window)
		: m_Camera(camera), m_Window(window)
	{
		m_ProjectionMatrix = m_Camera->GetProjectionMatrix();
		m_ViewMatrix = m_Camera->GetViewMatrix();
		std::cout << "Mouse Picker Constructed" << std::endl;
	}

	void MousePicker::Update(Entity& entity)
	{
		m_ViewMatrix = m_Camera->GetViewMatrix();
		m_CurrentRay = GetCurrentRay();

		if (IntersectionInRange(0.0f, m_RayRange, m_CurrentRay))
			m_CurrentGridPoint = BinarySearch(0, 0.0f, m_RayRange, m_CurrentRay);
		else
			m_CurrentGridPoint = { -1.0f, -1.0f, -1.0f };
	}

	glm::vec3 MousePicker::GetCurrentGridPoint()
	{
		return m_CurrentGridPoint;
	}

	glm::vec3 MousePicker::GetCurrentRay()
	{
		return m_CurrentRay;
	}

	glm::vec3 MousePicker::CalculateMouseRay()
	{
		double mouseX;
		double mouseY;
		glfwGetCursorPos(m_Window, &mouseX, &mouseY);

		float x = (2.0f * (float)mouseX) / 1800.0f - 1.0f;
		float y = 1.0f - (2.0f * (float)mouseY) / 1200.0f;

		glm::vec4 rayEye = m_ProjectionMatrix * glm::vec4(x, y, -1.0f, 1.0f);
		return glm::normalize(glm::inverse(m_Camera->GetViewMatrix()) * glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f));
	}

	glm::vec3 MousePicker::GetPointOnRay(glm::vec3 ray, float distance)
	{
		glm::vec3 start = m_Camera->GetPosition();
		glm::vec3 scaledRay = { ray.x * distance, ray.y * distance, ray.z * distance };

		return { start + scaledRay };
	}

	glm::vec3 MousePicker::BinarySearch(int count, float start, float finish, glm::vec3 ray)
	{
		float half = start + ((finish - start) / 2.0f);

		if (count >= m_RecursiveCount)
			return GetPointOnRay(ray, half);

		if (IntersectionInRange(start, half, ray))
			return BinarySearch(count + 1, start, half, ray);
		else
			return BinarySearch(count + 1, half, finish, ray);
	}

	bool MousePicker::IntersectionInRange(float start, float finish, glm::vec3 ray)
	{
		glm::vec3 startPoint = GetPointOnRay(ray, start);
		glm::vec3 endPoint = GetPointOnRay(ray, finish);

		if (!IsBelowGrid(startPoint) && IsBelowGrid(endPoint))
			return true;
		else
			return false;
	}

	bool MousePicker::IsBelowGrid(glm::vec3 testPoint)
	{
		float height = 0;
		if (testPoint.x > 0 && testPoint.x < 2)
			//TODO: correct this
			//height = terrainPos[floor(testPoint.x) * 3 + 1];
			height = 2;

		if (testPoint.y < height)
			return true;
		else
			return false;
	}

}