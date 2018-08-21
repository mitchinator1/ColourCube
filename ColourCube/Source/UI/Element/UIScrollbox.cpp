#include "UIScrollbox.h"
#include "UISlider.h"
#include "UIButton.h"
#include "UIDragBar.h"

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
	
	void UIScrollbox::AddElement(std::unique_ptr<UIDragBar>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIScrollbox::AddTraits()
	{
		float size = 2.0f;

		auto slider = std::make_unique<UI::UISlider>();
		slider->X = maxX - size;
		slider->Y = size * 2.0f;
		slider->maxX = size;
		slider->maxY = maxY - (size * 2.0f);
		slider->colour = { 0.5f, 0.4f, 0.7f, 1.0f };
		//TODO: Set starting position of scrollbar
		AddElement(slider);

		size = 4.0f;

		auto button = std::make_unique<UI::UIButton>();
		button->X = maxX - size;
		button->maxX = size;
		button->maxY = size;
		button->colour = { 0.5f, 0.4f, 0.6f, 1.0f };
		button->m_MouseUp = ACTION::HIDE;

		auto text = std::make_shared<UI::UIText>();
		text->SetFont("Arial")->SetKey("PopupClose")->SetSize(1.3f)->SetCenter();
		button->AddText(text);
		AddElement(button);

		auto bar = std::make_unique<UI::UIDragBar>();
		bar->maxX = maxX - m_Elements.back()->maxX;
		bar->maxY = m_Elements.back()->maxY;
		bar->SetValuePointer(this);
		AddElement(bar);
		
	}

}