#pragma once
#include "../Shader/ShaderFont.h"
#include "../Mesh/Font/FontType.h"
#include "../Mesh/Font/GUIText.h"
#include "../Mesh/VertexArray.h"

#include <vector>
#include <unordered_map>
#include <memory>


namespace Renderer
{
	class RendererFont
	{
	private:
		std::unique_ptr<Shader::ShaderFont> m_Shader;
		Text::GUIText* m_GUIText;
		Text::FontType* m_FontType;

	public:
		RendererFont();
		~RendererFont();

		void LoadVAO(std::vector<float>& vertexPositions, std::vector<float>& textureCoords);

		//void Render(std::unordered_map<Text::FontType, std::vector<Text::GUIText>>& texts);
		void Render();

	private:
		void Prepare();
		void RenderText(Text::GUIText& text);
		void EndRendering();

	};
}