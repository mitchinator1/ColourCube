#include "MouseBase.h"
#include "../Camera/CameraBase.h"

namespace Input
{
	MouseBase::MouseBase(std::shared_ptr<Display>& display)
		: m_Display(display), m_Camera(nullptr)
	{
	
	}

	void MouseBase::GetMouseInput()
	{
		if (glfwGetMouseButton(m_Display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_ToggledTime < glfwGetTime() - DELAY)
		{
			m_ToggledTime = (float)glfwGetTime();
			m_Toggled = true;
			glfwGetCursorPos(m_Display->Window, &mouseX, &mouseY);
		}
		else
		{
			m_Toggled = false;
		}
	}

	glm::vec3 MouseBase::CalculateMouseRay()
	{
		glm::vec2 normCoords = GetNormalizedDeviceCoords();
		glm::vec4 clipCoords = { normCoords.x, normCoords.y, -1.0f, 1.0f };
		glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
		glm::vec3 worldRay = ToWorldCoords(eyeCoords);

		return worldRay;
	}

	glm::vec2 MouseBase::GetNormalizedDeviceCoords()
	{
		float x = (2.0f * (float)mouseX) / m_Display->Width - 1.0f;
		float y = 1.0f - (2.0f * (float)mouseY) / m_Display->Height;

		return glm::vec2(x, y);
	}

	glm::vec4 MouseBase::ToEyeCoords(glm::vec4 clipCoords)
	{
		glm::vec4 eyeCoords = glm::inverse(m_Camera->GetProjectionMatrix()) * clipCoords;

		return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
	}

	glm::vec3 MouseBase::ToWorldCoords(glm::vec4 eyeCoords)
	{
		glm::vec4 rayWorld = glm::inverse(m_Camera->GetViewMatrix()) * eyeCoords;
		glm::vec3 mouseRay = { rayWorld.x, rayWorld.y, rayWorld.z };

		return glm::normalize(mouseRay);
	}
}