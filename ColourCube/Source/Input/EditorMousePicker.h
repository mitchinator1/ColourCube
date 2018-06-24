#ifndef EDITOR_MOUSE_PICKER_H
#define EDITOR_MOUSE_PICKER_H
#include "Mouse3D.h"

namespace Input
{
	class EditorMousePicker : public Mouse3D
	{
	private:
		bool m_AddCubeToggled				= true;
		bool m_ShowSelection				= false;

	public:
		EditorMousePicker(std::shared_ptr<Camera::CameraBase>& camera, std::shared_ptr<Display>& display);
		~EditorMousePicker() {}

		void HandleEvents()													override;
		void Update(Level& level)											override;
		bool ToggleMode()													override;
		void CalculateTargets(std::vector<std::unique_ptr<Cube>>& cubes)	override;
		
	private:
		void CubeIntersection(Level& level);
		void AddCube(Level& level);

	};
}

#endif