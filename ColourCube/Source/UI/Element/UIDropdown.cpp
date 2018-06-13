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

	bool UIDropdown::InRange(float x, float y)
	{
		if (x >= minX && y >= minY &&
			x <= minX + maxX && y <= minY + maxY)
		{
			return true;
		}

		for (auto& box : m_Elements)
		{
			if (box->IsHidden())
			{
				continue;
			}
			if (box->InRange(x, y))
			{
				return true;
			}
		}

		return false;
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

	ACTION UIDropdown::OnMouseOver()
	{
		if (!m_IsMouseOver)
		{
			if (GetAlpha() != 0.5f)
				SetAlpha(0.5f);

			Reveal();
			m_IsMouseOver = true;
		}
		return m_MouseOver;
	}

	ACTION UIDropdown::OnMouseOut()
	{
		if (m_IsMouseOver)
		{
			if (GetAlpha() < 0.6f)
				SetAlpha(m_PersistantAlpha);

			Hide(false);
			m_IsMouseOver = false;
			for (auto& element : m_Elements)
			{
				element->OnMouseOut();
			}
		}
		return m_MouseOut;
	}

	ACTION UIDropdown::OnMouseDown()
	{
		for (auto& button : m_Elements)
		{
			if (button->IsMouseOver())
			{
				return button->OnMouseDown();
			}
		}
		return m_MouseDown;
	}

	ACTION UIDropdown::OnMouseUp()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				auto action = element->OnMouseUp();
				return action;
			}
		}
		return m_MouseUp;
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

		m_Hidden = false;

		if (m_Text != nullptr)
			m_Text->Reveal();
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
			if (m_Text)
				m_Text->Hide();
		}
	}

	void UIDropdown::Build()
	{
		if (!m_Mesh)
		{
			m_Mesh = std::make_unique<Mesh>(CalculateVertices(), 2, 3);
		}

		for (auto& element : m_Elements)
		{
			element->minX += minX;
			element->minY += minY;
			element->Build();
		}

		if (m_Hidden)
		{
			for (auto& element : m_Elements)
				element->Hide();

			if (m_Text)
				m_Text->Hide();
		}

		if (m_Text)
		{
			if (m_Text->IsCentered())
			{
				m_Text->SetPosition(minX + (maxX / 2.0f) - 50.0f, minY)->SetCenter(true);
			}
			else
			{
				m_Text->SetPosition(minX + m_Text->GetPosition().x, minY + m_Text->GetPosition().y);
			}
		}
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
				return true;
		}

		return m_IsMouseDown;
	}

}