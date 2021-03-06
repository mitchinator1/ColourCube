#include "UIPopup.h"
#include "UISlider.h"
#include "UIButton.h"
#include "UIDragBar.h"

namespace UI
{
	UIPopup::UIPopup() noexcept
	{

	}

	UIPopup::~UIPopup()
	{

	}

	void UIPopup::Hide(bool hide)
	{
		OnMouseOut();

		for (auto& element : m_Elements)
		{
			element->Hide();
		}
		if (hide)
		{
			m_Hidden = true;
			m_UpdateNeeded = true;
			if (m_Text)
				m_Text->Hide();
		}
	}

	void UIPopup::AddElement(std::shared_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIPopup::AddElement(std::shared_ptr<UISlider>& element)
	{
		if (!m_Elements.empty())
		{
			if (m_Elements.size() == 1)
				element->SetValuePointer(&m_Elements.front()->colour.r);
			if (m_Elements.size() == 2)
				element->SetValuePointer(&m_Elements.front()->colour.g);
			if (m_Elements.size() == 3)
				element->SetValuePointer(&m_Elements.front()->colour.b);
		}

		m_Elements.emplace_back(std::move(element));
	}

	void UIPopup::AddElement(std::shared_ptr<UIButton>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIPopup::AddElement(std::shared_ptr<UIDragBar>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	glm::vec4& UIPopup::GetColour()
	{
		return m_Elements.front()->GetColour();
	}

	void UIPopup::AddTraits()
	{
		float size = 4.0f;

		auto button = std::make_shared<UI::UIButton>();
		button->position.x = width - size;
		button->width = size;
		button->height = size;
		button->colour = { 0.5f, 0.4f, 0.7f, 1.0f };
		button->m_MouseUp = ACTION::HIDE;

		auto text = std::make_shared<UI::UIText>();
		text->SetFont("Arial")->SetKey("PopupClose")->SetSize(1.3f)->SetCenter();
		button->AddText(text);
		AddElement(button);

		auto bar = std::make_shared<UI::UIDragBar>();
		bar->width = width - m_Elements.back()->width;
		bar->height = m_Elements.back()->height;
		bar->SetValuePointer(this);
		AddElement(bar);
	}

}