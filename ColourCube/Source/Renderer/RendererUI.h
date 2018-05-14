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

		void Render(UI::UIMaster& ui) const;

	private:
		void PrepareText() const;
		void PrepareElement() const;

		void EndRenderingText() const;
		void EndRenderingElement()const;
	};
}

#endif