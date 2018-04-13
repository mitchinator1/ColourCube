#include "MousePicker.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"
#include "../Camera/CameraBase.h"
#include "../Display.h"
#include "../Level/Level.h"
#include "GLFW/glfw3.h"

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
		if (MouseButtonIsPressed)
		{
			m_ViewMatrix = m_Camera->GetViewMatrix();
			m_CurrentRay = CalculateMouseRay();

			CubeIntersection(m_CurrentRay, level);
		}
	}

	void MousePicker::GetMouseInput()
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
		auto cubes = level.GetCubes();
		glm::vec3 start = m_Camera->GetPosition();
		glm::vec3 mouseRay;

		glm::vec3 pickedCube = { -1.0f, -1.0f, -1.0f };
		for (unsigned int i = 0; i < 200; ++i)
		{
			mouseRay = start + (ray * (i / 25.0f));
			for (auto& cube : cubes)
			{
				glm::vec3 target = cube.GetPosition();
				if (mouseRay.x >= target.x - 0.5f && mouseRay.x <= target.x + 0.5f &&
					mouseRay.z >= target.z - 0.5f && mouseRay.z <= target.z + 0.5f &&
					mouseRay.y >= target.y - 0.5f && mouseRay.y <= target.y + 0.5f)
				{

					Face face = Face::BOTTOM;
					
					if (mouseRay.z > target.z + 0.48f && mouseRay.x > target.x - 0.49f && mouseRay.x < target.x + 0.49f)
						face = Face::SOUTH;
					else if (mouseRay.z < target.z - 0.48f && mouseRay.x > target.x - 0.49f && mouseRay.x < target.x + 0.49f)
						face = Face::NORTH;
					else if (mouseRay.x > target.x + 0.48f && mouseRay.z > target.z - 0.49f && mouseRay.z < target.z + 0.49f)
						face = Face::EAST;
					else if (mouseRay.x < target.x - 0.48f && mouseRay.z > target.z - 0.49f && mouseRay.z < target.z + 0.49f)
						face = Face::WEST;

					//std::cout << "Cube: " << target.x << ", " << target.y << ", " << target.z << '\n'
					std::cout << "Face: " << (int)face << '\n';
					//std::cout << mouseRay.x << ", " << mouseRay.y << ", " << mouseRay.z << std::endl;

					level.ChangeColour((int)target.x, (int)target.y, (int)target.z, face);
					return;
				}
			}
		}
	}

}