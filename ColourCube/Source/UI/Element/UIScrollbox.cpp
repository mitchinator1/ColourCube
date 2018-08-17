#include "UIScrollbox.h"
#include "UISlider.h"
#include "UIButton.h"

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

	void UIScrollbox::AddTraits()
	{
		float size = 2.0f;

		auto slider = std::make_unique<UI::UISlider>();
		slider->minX = maxX - size;
		slider->minY = size * 2.0f;
		slider->maxX = size;
		slider->maxY = maxY - (size * 2.0f);
		slider->colour = { 0.5f, 0.4f, 0.7f, 1.0f };
		slider->SetValue(1.0f);
		AddElement(slider);

		size = 4.0f;

		auto button = std::make_unique<UI::UIButton>();
		button->minX = maxX - size;
		button->maxX = size;
		button->maxY = size;
		button->colour = { 0.5f, 0.4f, 0.6f, 1.0f };
		button->m_MouseUp = ACTION::HIDE;

		auto text = std::make_shared<UI::UIText>();
		text->SetFont("Arial")->SetKey("PopupClose")->SetSize(1.3f)->SetCenter();
		button->AddText(text);
		AddElement(button);

		//Add Drag Bar
	}

}