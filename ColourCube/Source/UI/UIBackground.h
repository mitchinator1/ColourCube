#ifndef UI_BACKGROUND_H
#define UI_BACKGROUND_H
#include <vector>
#include <memory>
#include "GLM/glm.hpp"

class Mesh;

namespace UI
{
	class UIBackground
	{
	private:
		float m_X, m_Y, m_XSize, m_YSize;
		glm::vec3 m_Colour;
		glm::vec3 m_Position;
		float m_Alpha;
		float m_Depth;

		std::unique_ptr<Mesh> m_Mesh;

	public:
		UIBackground(float x, float y, float xSize, float ySize, glm::vec3 colour, float alpha = 0.4f, float depth = 0.0f);
		~UIBackground();

		void Bind();
		void Unbind();

		void SetAlpha(float alpha);
		void SetPosition(glm::vec3 position);

		unsigned int GetCount();

		inline auto GetAlpha() { return m_Alpha; }
		inline auto GetPosition() { return m_Position; }

	private:
		std::vector<float> CalculateVertices(float x, float y, float xSize, float ySize, glm::vec3 c);

	};
}

#endif