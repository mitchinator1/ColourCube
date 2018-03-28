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
		float m_SizeX;
		float m_SizeY;
		bool m_Centered;

		std::vector<float> m_Vertices;

	public:
		UIBackground(float x, float y, float sizeX, float sizeY, bool centered = false);
		~UIBackground();

		std::vector<float>& GetVertices() { return m_Vertices; }

	private:
		std::vector<float> CalculateVertices(float x, float y, float sizeX, float sizeY);

	};
}

#endif