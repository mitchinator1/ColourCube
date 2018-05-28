#ifndef RENDERER_UI_H
#define RENDERER_UI_H
#include <memory>
#include "../UI/UIMaster.h"

namespace Shader { class ShaderBase; }
namespace UI { class UIElement; }

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

		void Render(UI::UIMaster& ui) const;

	private:
		void PrepareText() const;
		void RenderElements(std::vector<std::unique_ptr<UI::UIElement>>& elements) const;
		void PrepareElement() const;

		void EndRenderingText() const;
		void EndRenderingElement()const;
	};
}

#endif