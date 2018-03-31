#include "UIMaster.h"
#include "Font/FontType.h"
#include <iostream>

namespace UI
{
	UIMaster::UIMaster()
		: m_BackgroundMesh(nullptr), m_TextMesh(nullptr)
	{

	}

	UIMaster::~UIMaster()
	{

	}

	void UIMaster::AddElement(UIButton& button)
	{

	}

	void UIMaster::AddBackground(UIBackground& background)
	{
		m_Backgrounds.emplace_back(background);
	}

	void UIMaster::AddText(std::shared_ptr<Text::FontType> font, UIText& text)
	{
		m_Texts[font].emplace_back(text);
	}

	void UIMaster::AddButton(UIButton& button)
	{
		AddBackground(button.GetBackground());
		AddText(button.GetText().GetFont(), button.GetText());
	}

	void UIMaster::CalculateMesh()
	{
		std::vector<float> vertices;

		for (auto& background : m_Backgrounds)
			vertices.insert(vertices.end(), background.GetVertices().begin(), background.GetVertices().end());

		m_BackgroundMesh = new Mesh(vertices, 2, 3);

		//vertices.clear();

		//for (auto& text : m_Texts)
		//	vertices.insert(vertices.end(), text.GetVertices().begin(), text.GetVertices().end());

		//m_TextMesh = new Mesh(vertices, 2, 2);
	}

	void UIMaster::Bind()
	{
		m_BackgroundMesh->Bind();
	}

	void UIMaster::Unbind()
	{
		m_BackgroundMesh->Unbind();
	}
}