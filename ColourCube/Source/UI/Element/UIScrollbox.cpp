#include "UIScrollbox.h"
#include "UISlider.h"
#include "UIButton.h"

#include <iostream>

namespace UI
{
	UIScrollbox::UIScrollbox()
	{
	}

	UIScrollbox::~UIScrollbox()
	{

	}

	void UIScrollbox::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIScrollbox::AddElement(std::unique_ptr<UISlider>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIScrollbox::AddElement(std::unique_ptr<UIButton>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIScrollbox::Build()
	{
		for (auto& element : m_Elements)
		{
			element->minX += minX;
			element->minY += minY;
			element->Z += Z;
			element->Build();
		}

		AddTraits();

		if (m_Hidden)
		{
			for (auto& element : m_Elements)
				element->Hide();

			if (m_Text)
				m_Text->Hide();
		}

		UpdateTextPosition();
	}

	void UIScrollbox::AddTraits()
	{
		auto slider = std::make_unique<UI::UISlider>();
		float size = 2.5f;
		slider->minX = minX + maxX - size;
		slider->minY = minY + 5.0f;
		slider->maxX = size;
		slider->maxY = maxY;
		slider->Z += Z;
		slider->colour = { 0.5f, 0.4f, 0.7f, 1.0f };
		slider->Build();
		AddElement(slider);

		//Add button
		auto button = std::make_unique<UI::UIButton>();
		size = 5.0f;
		button->minX = minX + maxX - size;
		button->minY = minY;
		button->maxX = size;
		button->maxY = size;
		button->Z += Z;
		button->colour = { 0.5f, 0.4f, 0.7f, 1.0f };
		button->m_MouseUp = ACTION::HIDE;
		//Add text and action;
		button->Build();
		AddElement(button);

		//Add Drag Bar
	}

}