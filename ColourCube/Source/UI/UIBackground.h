#ifndef UI_BACKGROUND_H
#define UI_BACKGROUND_H
#include "GLM/glm.hpp"
#include <vector>

namespace UI
{
	class UIBackground
	{
	private:
		glm::vec2 m_Position;
		float m_Size;

		std::vector<float> m_Vertices;

	public:
		UIBackground(glm::vec2 position, float size);
		~UIBackground();

		std::vector<float>& GetVertices() { return m_Vertices; }

	private:
		std::vector<float> CalculateVertices(glm::vec2 position, float size);

	};
}

#endif