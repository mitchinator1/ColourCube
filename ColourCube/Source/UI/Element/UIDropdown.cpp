#include "UIDropdown.h"
#include "UIButton.h"

namespace UI
{
	UIDropdown::UIDropdown() noexcept
	{

	}

	UIDropdown::~UIDropdown()
	{

	}

	void UIDropdown::Update()
	{
		for (auto& element : m_Elements)
		{
			element->Update();
		}
	}

	void UIDropdown::Reveal(bool reveal)
	{
		if (reveal)
		{
			for (auto& element : m_Elements)
			{
				element->Reveal(false);
			}
		}

		if (m_Text)
			m_Text->Reveal();

		m_Hidden = false;
		m_UpdateNeeded = true;
	}

	void UIDropdown::Hide(bool hide)
	{
		for (auto& element : m_Elements)
		{
			element->Hide();
		}
		if (hide)
		{
			m_Hidden = true;
			OnMouseOut();
			if (m_Text)
				m_Text->Hide();
		}
	}

	ACTION UIDropdown::OnMouseOver()
	{
		if (!m_IsMouseOver)
		{
			if (colour.a != 0.7f)
				colour.a = 0.7f;

			Reveal();
			m_IsMouseOver = true;
		}
		return m_MouseOver;
	}

	ACTION UIDropdown::OnMouseOut()
	{
		if (m_IsMouseOver)
		{
			if (colour.a < 0.8f)
				colour.a = m_PersistantAlpha;

			Hide(false);
			m_IsMouseOver = false;
			for (auto& element : m_Elements)
			{
				if (element->IsMouseOver())
					element->OnMouseOut();
			}
		}
		return m_MouseOut;
	}
	
	ACTION UIDropdown::OnMouseDown()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseOver())
			{
				return element->OnMouseDown();
			}
		}
		return m_MouseDown;
	}

	ACTION UIDropdown::OnMouseUp()
	{
		m_IsMouseDown = false;
		auto action = m_MouseUp;

		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				action = element->OnMouseUp();
				Hide(false);
			}
		}
		return action;
	}

	void UIDropdown::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIDropdown::AddElement(std::unique_ptr<UIButton>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIDropdown::AddElement(std::unique_ptr<UIDropdown>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	std::string& UIDropdown::GetID()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseOver())
			{
				return element->GetID();
			}
		}
		return m_ID;
	}

	bool UIDropdown::IsMouseDown()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				return true;
			}
		}

		return m_IsMouseDown;
	}

}