#ifndef EDITOR_MOUSE_PICKER_H
#define EDITOR_MOUSE_PICKER_H
#include "Mouse3D.h"

enum class Face;

namespace Input
{
	class EditorMousePicker : public Mouse3D
	{
	private:
		bool m_AddCubeToggled	= true;
		bool m_ShowSelection	= true;
		glm::vec3 m_Selection	= { 0.0f, 0.0f, 0.0f };
		Face m_SelectionFace;
		Cube* m_TempCube		= nullptr;
		glm::vec3 m_AddColour	= { 0.3f, 0.7f, 0.2f };
		glm::vec3 m_RemoveColour = { 0.7f, 0.3f, 0.2f };

	public:
		EditorMousePicker(std::shared_ptr<Camera::CameraBase>& camera, std::shared_ptr<Display>& display);
		~EditorMousePicker() {}

		void HandleEvents()													override;
		void Update(Level& level)											override;
		bool ToggleMode()													override;
		void CalculateTargets(std::vector<std::unique_ptr<Cube>>& cubes)	override;
		
	private:
		void HandleSelection(Level& level);
		void HandleToggle(Level& level);

		void ShowSelection(Level& level);
		void HideSelection(Level& level);
		void AddCube(Level& level);
		void RemoveCube(Level& level);
		bool TempCubeSelected();
		Face GetSelectedFace();

	};
}

#endif