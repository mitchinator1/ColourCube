#include "MousePicker.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"
#include <iostream>

namespace Input
{
	MousePicker::MousePicker(Camera::CameraBase* camera, GLFWwindow* window)
		: m_Camera(camera), m_Window(window)
	{
		m_ProjectionMatrix = m_Camera->GetProjectionMatrix();
		m_ViewMatrix = m_Camera->GetViewMatrix();
	}

	void MousePicker::HandleEvents(Entity& entity)
	{
		GetMouseInput();
	}

	void MousePicker::Update(Entity& entity)
	{
		if (MouseButtonIsPressed)
		{
			m_ViewMatrix = m_Camera->GetViewMatrix();
			m_CurrentRay = CalculateMouseRay();

			if (IntersectionInRange(0.0f, m_RayRange, m_CurrentRay))
			{
				m_CurrentPoint = BinarySearch(0, 0.0f, m_RayRange, m_CurrentRay);
			}
			else
			{
				m_CurrentPoint = { -1.0f, -1.0f, -1.0f };
			}
			entity.Receive(m_CurrentRay);
		}
	}

	void MousePicker::GetMouseInput()
	{
		if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && Toggled < glfwGetTime() - 0.15f)
		{
			Toggled = (float)glfwGetTime();
			MouseButtonIsPressed = true;
			glfwGetCursorPos(m_Window, &mouseX, &mouseY);
		}
		else
		{
			MouseButtonIsPressed = false;
		}
	}

	glm::vec3 MousePicker::GetCurrentPoint()
	{
		return m_CurrentPoint;
	}

	glm::vec3 MousePicker::GetCurrentRay()
	{
		return m_CurrentRay;
	}

	glm::vec3 MousePicker::CalculateMouseRay()
	{
		glm::vec2 normCoords = getNormalizedDeviceCoords((float)mouseX, (float)mouseY);
		glm::vec4 clipCoords = { normCoords.x, normCoords.y, -1.0f, 1.0f };
		glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
		glm::vec3 worldRay = ToWorldCoords(eyeCoords);

		return worldRay;
	}

	glm::vec3 MousePicker::ToWorldCoords(glm::vec4 eyeCoords)
	{
		glm::vec4 rayWorld = glm::inverse(m_ViewMatrix) * eyeCoords;
		glm::vec3 mouseRay = { rayWorld.x, rayWorld.y, rayWorld.z };

		return glm::normalize(mouseRay);
	}

	glm::vec4 MousePicker::ToEyeCoords(glm::vec4 clipCoords)
	{
		glm::vec4 eyeCoords = glm::inverse(m_ProjectionMatrix) * clipCoords;

		return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
	}

	glm::vec2 MousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY)
	{
		float x = (2.0f * mouseX) / 1800.0f - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / 1200.0f;

		return glm::vec2(x, y);
	}

	glm::vec3 MousePicker::GetPointOnRay(glm::vec3 ray, float distance)
	{
		glm::vec3 start = m_Camera->GetPosition();
		glm::vec3 scaledRay = { ray.x + distance, ray.y + distance, ray.z + distance };

		return { start + scaledRay };
	}

	glm::vec3 MousePicker::BinarySearch(int count, float start, float finish, glm::vec3 ray)
	{
		float half = start + ((finish - start) / 2.0f);

		if (count >= m_RecursiveCount)
			return GetPointOnRay(ray, half);

		if (IntersectionInRange(start, half, ray))
			return BinarySearch(count++, start, half, ray);
		else
			return BinarySearch(count++, half, finish, ray);
	}

	bool MousePicker::IntersectionInRange(float start, float finish, glm::vec3& ray)
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
		float height = 0.0f;
		if (testPoint.y > 0.0f && testPoint.y < 55.0f)
			//TODO: correct this
			//height = terrainPos[floor(testPoint.x) * 3 + 1];
			height = 60.0f;

		if (testPoint.y < height)
			return true;
		else
			return false;
	}

}