#ifndef UI_BACKGROUND_H
#define UI_BACKGROUND_H
#include "GLM/glm.hpp"
#include <vector>
#include "../Mesh/Mesh.h"

namespace UI
{
	class UIBackground
	{
	private:
		glm::vec2 m_Position;
		float m_SizeX;
		float m_SizeY;
		bool m_Centered;

		Mesh* m_Mesh;

	public:
		UIBackground(float x, float y, float sizeX, float sizeY, bool centered = false);
		~UIBackground();

		void Bind();
		void Unbind();

		inline unsigned int GetCount() { return m_Mesh->GetCount(); }

	private:
		std::vector<float> CalculateVertices(float x, float y, float sizeX, float sizeY);

	};
}

#endif