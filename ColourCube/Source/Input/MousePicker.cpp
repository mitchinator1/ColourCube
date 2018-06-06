#include "MousePicker.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"
#include "../Camera/CameraBase.h"
#include "../Display.h"
#include "../Level/Level.h"
#include "../Level/Cube.h"

namespace Input
{
	MousePicker::MousePicker(std::shared_ptr<Camera::CameraBase> camera, std::shared_ptr<Display> display)
		: m_Camera(camera), m_Display(display)
	{
		m_ProjectionMatrix = m_Camera->GetProjectionMatrix();
		m_ViewMatrix = m_Camera->GetViewMatrix();
	}

	void MousePicker::HandleEvents()
	{
		GetMouseInput();
	}

	void MousePicker::Update(Level& level)
	{
		if (m_MouseButtonIsPressed)
		{
			m_ViewMatrix = m_Camera->GetViewMatrix();
			m_CurrentRay = CalculateMouseRay();

			CubeIntersection(m_CurrentRay, level);
		}
	}

	bool MousePicker::ToggleMode()
	{
		return false;
	}

	void MousePicker::GetMouseInput()
	{
		if (glfwGetMouseButton(m_Display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_ToggledTime < glfwGetTime() - DELAY)
		{
			m_ToggledTime = (float)glfwGetTime();
			m_MouseButtonIsPressed = true;
			glfwGetCursorPos(m_Display->Window, &mouseX, &mouseY);
		}
		else
		{
			m_MouseButtonIsPressed = false;
		}
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
		float x = (2.0f * mouseX) / m_Display->Width - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / m_Display->Height;

		return glm::vec2(x, y);
	}

	void MousePicker::CubeIntersection(glm::vec3 ray, Level& level)
	{
		glm::vec3 start = m_Camera->GetPosition();
		glm::vec3 curRay;

		for (unsigned int i = 0; i < m_RecursiveCount; ++i)
		{
			curRay = start + (ray * (i / 30.0f));
			for (auto& cube : level.GetCubes())
			{
				glm::vec3 target = cube.GetPosition();
				if (curRay.x >= target.x - 0.5f && curRay.x <= target.x + 0.5f &&
					curRay.z >= target.z - 0.5f && curRay.z <= target.z + 0.5f &&
					curRay.y >= target.y - 0.5f && curRay.y <= target.y + 0.5f)
				{
					glm::vec3 newRay = (curRay + (start + (ray * ((i - 1) / 30.0f)))) / 2.0f;
					float epsilon = 0.015f;

						 if (abs(newRay.z - target.z - 0.5f) < epsilon && cube.CheckFace(Face::SOUTH))
					{
						level.ChangeColour((int)target.x, (int)target.y, (int)target.z, Face::SOUTH);
					}
					else if (abs(newRay.z - target.z + 0.5f) < epsilon && cube.CheckFace(Face::NORTH))
					{
						level.ChangeColour((int)target.x, (int)target.y, (int)target.z, Face::NORTH);
					}
					else if (abs(newRay.x - target.x + 0.5f) < epsilon && cube.CheckFace(Face::WEST))
					{
						level.ChangeColour((int)target.x, (int)target.y, (int)target.z, Face::WEST);
					}
					else if (abs(newRay.x - target.x - 0.5f) < epsilon && cube.CheckFace(Face::EAST))
					{
						level.ChangeColour((int)target.x, (int)target.y, (int)target.z, Face::EAST);
					}
					else if (abs(newRay.y - target.y - 0.5f) < epsilon && cube.CheckFace(Face::TOP))
					{
						level.ChangeColour((int)target.x, (int)target.y, (int)target.z, Face::TOP);
					}
					else if (abs(newRay.y - target.y + 0.5f) < epsilon && cube.CheckFace(Face::BOTTOM))
					{
						level.ChangeColour((int)target.x, (int)target.y, (int)target.z, Face::BOTTOM);
					}

					return;
				}
			}
		}
	}

}