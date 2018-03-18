#pragma once
#include "../Entity.h"
#include "../Shader/ShaderBase.h"

namespace Renderer
{
	class RendererBase
	{
	private:
		//Shader::ShaderBase* m_Shader;
	public:
		RendererBase();
		~RendererBase();

		void Clear() const;
		//void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const;
		//void Draw(VertexArray& va, IndexBuffer& ib) const;
		//void Draw(Level& level) const;
		void Draw(const Entity* entity) const;
	};
}