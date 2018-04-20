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
		float m_Alpha;

		std::unique_ptr<Mesh> m_Mesh;

	public:
		UIBackground(float x, float y, float xSize, float ySize, glm::vec3 colour, float alpha = 0.4f);
		~UIBackground();

		void Bind();
		void Unbind();

		inline auto GetAlpha() { return m_Alpha; }
		inline auto GetCount() { return m_Mesh->GetCount(); }

	private:
		std::vector<float> CalculateVertices(float x, float y, float xSize, float ySize, glm::vec3 c);

	};
}

#endif