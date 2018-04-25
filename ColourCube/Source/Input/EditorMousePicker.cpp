#include "EditorMousePicker.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"
#include "../Camera/CameraBase.h"
#include "../Display.h"
#include "../Level/Level.h"
#include "../Level/Cube.h"
#include "GLFW/glfw3.h"

namespace Input
{
	EditorMousePicker::EditorMousePicker(std::shared_ptr<Camera::CameraBase> camera, std::shared_ptr<Display> display)
		: m_Camera(camera), m_Display(display)
	{
		m_ProjectionMatrix = m_Camera->GetProjectionMatrix();
		m_ViewMatrix = m_Camera->GetViewMatrix();
	}

	void EditorMousePicker::HandleEvents()
	{
		GetMouseInput();
	}

	void EditorMousePicker::Update(Level& level)
	{
		if (MouseButtonIsPressed)
		{
			m_ViewMatrix = m_Camera->GetViewMatrix();
			m_CurrentRay = CalculateMouseRay();

			CubeIntersection(m_CurrentRay, level);
		}
	}

	void EditorMousePicker::GetMouseInput()
	{
		if (glfwGetMouseButton(m_Display->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && Toggled < glfwGetTime() - 0.15f)
		{
			Toggled = (float)glfwGetTime();
			MouseButtonIsPressed = true;
			glfwGetCursorPos(m_Display->Window, &mouseX, &mouseY);
		}
		else
		{
			MouseButtonIsPressed = false;
		}
	}

	glm::vec3 EditorMousePicker::CalculateMouseRay()
	{
		glm::vec2 normCoords = getNormalizedDeviceCoords((float)mouseX, (float)mouseY);
		glm::vec4 clipCoords = { normCoords.x, normCoords.y, -1.0f, 1.0f };
		glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
		glm::vec3 worldRay = ToWorldCoords(eyeCoords);

		return worldRay;
	}

	glm::vec3 EditorMousePicker::ToWorldCoords(glm::vec4 eyeCoords)
	{
		glm::vec4 rayWorld = glm::inverse(m_ViewMatrix) * eyeCoords;
		glm::vec3 mouseRay = { rayWorld.x, rayWorld.y, rayWorld.z };

		return glm::normalize(mouseRay);
	}

	glm::vec4 EditorMousePicker::ToEyeCoords(glm::vec4 clipCoords)
	{
		glm::vec4 eyeCoords = glm::inverse(m_ProjectionMatrix) * clipCoords;

		return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
	}

	glm::vec2 EditorMousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY)
	{
		float x = (2.0f * mouseX) / m_Display->Width - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / m_Display->Height;

		return glm::vec2(x, y);
	}

	void EditorMousePicker::CubeIntersection(glm::vec3 ray, Level& level)
	{
		glm::vec3 start = m_Camera->GetPosition();
		glm::vec3 curRay;

		std::vector<glm::vec3> targets = {
		{ -2.0f,	-1.0f,	-2.0f },
		{ -1.0f,	-1.0f,	-2.0f },
		{ 0.0f,		-1.0f,	-2.0f },
		{ 1.0f,		-1.0f,	-2.0f },
		{ 2.0f,		-1.0f,	-2.0f },
		{ -2.0f,	-1.0f,	-1.0f },
		{ -1.0f,	-1.0f,	-1.0f },
		{ 0.0f,		-1.0f,	-1.0f },
		{ 1.0f,		-1.0f,	-1.0f },
		{ 2.0f,		-1.0f,	-1.0f },
		{ -2.0f,	-1.0f,	0.0f },
		{ -1.0f,	-1.0f,	0.0f },
		{ 0.0f,		-1.0f,	0.0f },
		{ 1.0f,		-1.0f,	0.0f },
		{ 2.0f,		-1.0f,	0.0f },
		{ -2.0f,	-1.0f,	1.0f },
		{ -1.0f,	-1.0f,	1.0f },
		{ 0.0f,		-1.0f,	1.0f },
		{ 1.0f,		-1.0f,	1.0f },
		{ 2.0f,		-1.0f,	1.0f },
		{ -2.0f,	-1.0f,	2.0f },
		{ -1.0f,	-1.0f,	2.0f },
		{ 0.0f,		-1.0f,	2.0f },
		{ 1.0f,		-1.0f,	2.0f },
		{ 2.0f,		-1.0f,	2.0f },
		};

		for (unsigned int i = 0; i < m_RecursiveCount; ++i)
		{
			curRay = start + (ray * (i / 30.0f));
			//for (auto& cube : level.GetCubes())
			//{
				//glm::vec3 target = cube.GetPosition();
			for (auto& target : targets)
			{
				if (curRay.x >= target.x - 0.5f && curRay.x <= target.x + 0.5f &&
					curRay.z >= target.z - 0.5f && curRay.z <= target.z + 0.5f &&
					curRay.y >= target.y - 0.5f && curRay.y <= target.y + 0.5f)
				{
					glm::vec3 newRay = (curRay + (start + (ray * ((i - 1) / 30.0f)))) / 2.0f;
					float epsilon = 0.015f;

					if (abs(newRay.z - target.z - 0.5f) < epsilon)// (Face::SOUTH)
					{
						level.AddCube(target.x, target.y, target.z + 1, Face::NORTH);
					}
					else if (abs(newRay.z - target.z + 0.5f) < epsilon)// (Face::NORTH)
					{
						level.AddCube(target.x, target.y, target.z - 1, Face::SOUTH);
					}
					else if (abs(newRay.x - target.x + 0.5f) < epsilon)// (Face::WEST)
					{
						level.AddCube(target.x - 1, target.y, target.z, Face::EAST);
					}
					else if (abs(newRay.x - target.x - 0.5f) < epsilon)// (Face::EAST)
					{
						level.AddCube(target.x + 1, target.y, target.z, Face::WEST);
					}
					else if (abs(newRay.y - target.y - 0.5f) < epsilon)// (Face::TOP)
					{
						level.AddCube(target.x, target.y + 1, target.z, Face::BOTTOM);
					}
					else if (abs(newRay.y - target.y + 0.5f) < epsilon)// (Face::BOTTOM)
					{
						level.AddCube(target.x, target.y - 1, target.z, Face::TOP);
					}

					return;
				}
			}
		}
	}

}