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

	public:
		RendererFont();
		~RendererFont();

		void Prepare();
		void Render(Text::GUIText* text);
		void EndRendering();

	private:
		void RenderText(Text::GUIText& text);

	};
}