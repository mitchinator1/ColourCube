#ifndef UI_BACKGROUND_H
#define UI_BACKGROUND_H
#include "GLM/glm.hpp"
#include <vector>
#include <memory>
#include "../Mesh/Mesh.h"

namespace UI
{
	class UIBackground
	{
	private:
		float m_X, m_Y, m_XSize, m_YSize;
		glm::vec3 m_Colour;

		std::unique_ptr<Mesh> m_Mesh;

	public:
		UIBackground(float x, float y, float xSize, float ySize, glm::vec3 colour);
		~UIBackground();

		void Bind();
		void Unbind();

		inline unsigned int GetCount() { return m_Mesh->GetCount(); }

	private:
		std::vector<float> CalculateVertices(float x, float y, float xSize, float ySize, glm::vec3 c);

	};
}

#endif