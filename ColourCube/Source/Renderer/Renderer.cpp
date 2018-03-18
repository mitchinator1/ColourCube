#include "Renderer.h"
#include "GL/glew.h"

namespace Renderer
{
	RendererBase::RendererBase()
		//: m_Shader()
	{

	}

	RendererBase::~RendererBase()
	{

	}

	void RendererBase::Draw(const Entity* entity) const
	{
		entity->Draw();
	}

	void RendererBase::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}