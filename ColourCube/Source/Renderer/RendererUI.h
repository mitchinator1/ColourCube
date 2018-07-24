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
		RendererUI() noexcept;
		~RendererUI();

		void Render(UI::UIMaster* ui)	const;

	private:
		void PrepareElement()			const;
		void PrepareText()				const;

		void RenderElements(Mesh* mesh)	const;

		void EndRenderingElement()		const;
		void EndRenderingText()			const;
	};
}

#endif