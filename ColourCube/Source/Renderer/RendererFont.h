#pragma once
#include "GL/glew.h"
#include "../Mesh/Font/FontType.h"
#include "../Shader/ShaderFont.h"

#include <unordered_map>

namespace Renderer
{
	class RendererFont {
	private:
		Shader::ShaderFont* m_Shader;

	public:
		RendererFont();
		~RendererFont();

		void Render(std::unordered_map<Text::FontType, std::vector<Text::GUIText>> texts);

	private:
		void Prepare();
		void RenderText(Text::GUIText& text);
		void EndRendering();

	};
}