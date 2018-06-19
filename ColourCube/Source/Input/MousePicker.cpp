#include "MousePicker.h"
#include "../Camera/CameraBase.h"
#include "../Level/Level.h"

namespace Input
{
	MousePicker::MousePicker(std::shared_ptr<Camera::CameraBase>& camera, std::shared_ptr<Display>& display)
		: Mouse3D(display)
	{
		Mouse3D::m_Camera = camera;
	}

	void MousePicker::HandleEvents()
	{
		MouseBase::GetMouseInput();
	}

	void MousePicker::Update(Level& level)
	{
		if (m_Toggled)
		{
			m_CurrentRay = CalculateMouseRay();

			CubeIntersection(m_CurrentRay, level);
		}
	}

	bool MousePicker::ToggleMode()
	{
		return false;
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