#include "UIMaster.h"
#include <iostream>

namespace UI
{
	UIMaster::UIMaster()
		: m_Mesh(nullptr)
	{

	}

	UIMaster::~UIMaster()
	{

	}

	void UIMaster::AddBackground(UIBackground& background)
	{
		m_Backgrounds.emplace_back(background);
	}

	void UIMaster::CalculateMesh()
	{
		std::vector<float> vertices;

		for (auto& background : m_Backgrounds)
			vertices.insert(vertices.end(), background.GetVertices().begin(), background.GetVertices().end());

		m_Mesh = new Mesh(vertices, 2, 3);
	}

	void UIMaster::Bind()
	{
		m_Mesh->Bind();
	}

	void UIMaster::Unbind()
	{
		m_Mesh->Unbind();
	}
}