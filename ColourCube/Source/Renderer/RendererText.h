#ifndef RENDERER_FONT_H
#define RENDERER_FONT_H
//#include <vector>
//#include <unordered_map>
#include <memory>

namespace Shader { class ShaderBase; }
namespace UI { class UIText; }

namespace Renderer
{
	class RendererText
	{
	private:
		std::unique_ptr<Shader::ShaderBase> m_Shader;

	public:
		RendererText();
		~RendererText();

		void Prepare();
		void Render(UI::UIText* text);
		void EndRendering();

	};
}

#endif