#ifndef RENDERER_UI_H
#define RENDERER_UI_H
#include <memory>
#include "../UI/UIMaster.h"

namespace Shader { class ShaderBase; }

namespace Renderer
{
	class RendererUI
	{
	private:
		std::unique_ptr<Shader::ShaderBase> m_TextShader;
		std::unique_ptr<Shader::ShaderBase> m_ElementShader;

	public:
		RendererUI();
		~RendererUI();

		void Render(UI::UIMaster& ui);

	private:
		void PrepareText();
		void PrepareElement();

		void EndRenderingText();
		void EndRenderingElement();
	};
}

#endif