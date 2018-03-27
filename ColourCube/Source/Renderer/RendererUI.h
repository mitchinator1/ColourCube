#ifndef RENDERER_UI_H
#define RENDERER_UI_H
#include <memory>
#include "../UI/UIMaster.h"
#include "../Shader/ShaderUI.h"

namespace Renderer
{
	class RendererUI
	{
	private:
		std::unique_ptr<Shader::ShaderUI> m_Shader;

	public:
		RendererUI();
		~RendererUI();

		void Prepare();
		void Render(UI::UIMaster* ui);
		void EndRendering();
	};
}

#endif