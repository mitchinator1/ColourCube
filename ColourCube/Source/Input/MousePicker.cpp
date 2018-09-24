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
			CalculateMouseRay();

			if (MouseRayIntersects(level))
				CubeIntersection(level);
		}
	}

	bool MousePicker::ToggleMode()
	{
		return false;
	}

	void MousePicker::CalculateTargets(std::vector<std::unique_ptr<Cube>>& cubes)
	{
		m_Targets.clear();
		
		for (auto& cube : cubes)
		{
			m_Targets.emplace_back(cube->position);
		}
	}

	void MousePicker::CubeIntersection(Level& level)
	{
		const float epsilon = 0.015f;
		const float size	= 0.5f;
		const auto& camera	= m_Camera->position;

		if (camera.x > m_CurrentTarget.x && abs(m_CurrentRay.x - m_CurrentTarget.x - size) < epsilon)
				{
					level.ChangeColour((int)m_CurrentTarget.x, (int)m_CurrentTarget.y, (int)m_CurrentTarget.z, Face::EAST);
				}
		if (camera.x < m_CurrentTarget.x && abs(m_CurrentRay.x - m_CurrentTarget.x + size) < epsilon)
				{
					level.ChangeColour((int)m_CurrentTarget.x, (int)m_CurrentTarget.y, (int)m_CurrentTarget.z, Face::WEST);
				}
		if (camera.y > m_CurrentTarget.y && abs(m_CurrentRay.y - m_CurrentTarget.y - size) < epsilon)
				{
					level.ChangeColour((int)m_CurrentTarget.x, (int)m_CurrentTarget.y, (int)m_CurrentTarget.z, Face::TOP);
				}
		if (camera.y < m_CurrentTarget.y && abs(m_CurrentRay.y - m_CurrentTarget.y + size) < epsilon)
				{
					level.ChangeColour((int)m_CurrentTarget.x, (int)m_CurrentTarget.y, (int)m_CurrentTarget.z, Face::BOTTOM);
				}
		if (camera.z > m_CurrentTarget.z && abs(m_CurrentRay.z - m_CurrentTarget.z - size) < epsilon)
				{
					level.ChangeColour((int)m_CurrentTarget.x, (int)m_CurrentTarget.y, (int)m_CurrentTarget.z, Face::SOUTH);
				}
		if (camera.z < m_CurrentTarget.z && abs(m_CurrentRay.z - m_CurrentTarget.z + size) < epsilon)
				{
					level.ChangeColour((int)m_CurrentTarget.x, (int)m_CurrentTarget.y, (int)m_CurrentTarget.z, Face::NORTH);
				}

	}

}