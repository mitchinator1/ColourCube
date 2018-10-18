#include "UIScrollbox.h"
#include "UISlider.h"
#include "UIButton.h"
#include "UIDragBar.h"
#include "UITextEntry.h"

namespace UI
{
	UIScrollbox::UIScrollbox()
	{
		//TODO: Have elements scroll inside "Box".
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

	void UIScrollbox::AddElement(std::unique_ptr<UITextEntry>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIScrollbox::Deactivate()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsActive())
			{
				element->Deactivate();
			}
		}
	}

	bool UIScrollbox::IsActive() const
	{
		for (auto& element : m_Elements)
		{
			if (element->IsActive())
			{
				return true;
			}
		}

		return m_Active;
	}

	void UIScrollbox::AddTraits()
	{
		if (m_TraitsAdded)
		{
			return;
		}

		float size = 2.0f;

		auto slider = std::make_unique<UI::UISlider>();
		slider->position.x = width - size;
		slider->position.y = size * 2.0f;
		slider->width = size;
		slider->height = height - (size * 2.0f);
		slider->colour = { 0.5f, 0.4f, 0.7f, 1.0f };
		//TODO: Set starting position of scrollbar
		AddElement(slider);

		size = 4.0f;

		auto button = std::make_unique<UI::UIButton>();
		button->position.x = width - size;
		button->width = size;
		button->height = size;
		button->colour = { 0.5f, 0.4f, 0.6f, 1.0f };
		button->m_MouseUp = ACTION::HIDE;

		auto text = std::make_shared<UI::UIText>();
		text->SetFont("Arial")->SetKey("PopupClose")->SetSize(1.3f)->SetCenter();
		button->AddText(text);
		AddElement(button);

		auto bar = std::make_unique<UI::UIDragBar>();
		bar->width = width - m_Elements.back()->width;
		bar->height = m_Elements.back()->height;
		bar->SetValuePointer(this);
		AddElement(bar);

		auto textField = std::make_unique<UI::UITextEntry>();
		textField->width = width;
		textField->height = height;
		AddElement(textField);

		m_TraitsAdded = true;
	}

}