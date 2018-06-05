#include "UIPopup.h"
#include "UISlider.h"
#include "UIButton.h"

namespace UI
{
	UIPopup::UIPopup()
	{

	}

	UIPopup::~UIPopup()
	{

	}

	void UIPopup::Update()
	{
		for (auto& element : m_Elements)
		{
			element->Update();
		}
	}

	void UIPopup::Reveal(bool reveal)
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

	void UIPopup::Hide(bool hide)
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

	ACTION UIPopup::OnMouseOut()
	{
		for (auto& element : m_Elements)
		{
			element->OnMouseOut();
		}
		return m_MouseOut;
	}

	ACTION UIPopup::OnMouseDown()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseOver())
			{
				ACTION action = element->OnMouseDown();
				if (action == ACTION::HIDE)
				{
					Hide();
					return ACTION::NONE;
				}
				return action;
			}
		}
		return m_MouseDown;
	}

	ACTION UIPopup::OnMouseUp()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				return element->OnMouseUp();
			}
		}
		return m_MouseUp;
	}

	void UIPopup::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIPopup::AddElement(std::unique_ptr<UISlider>& element)
	{
		if (!m_Elements.empty())
		{
			if (m_Elements.size() == 1)
				element->SetValuePointer(&m_Elements.front()->colour.r);
			if (m_Elements.size() == 2)
				element->SetValuePointer(&m_Elements.front()->colour.g);
			if (m_Elements.size() == 3)
				element->SetValuePointer(&m_Elements.front()->colour.b);
			Update();
		}

		m_Elements.emplace_back(std::move(element));
	}

	void UIPopup::AddElement(std::unique_ptr<UIButton>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	bool UIPopup::InRange(float x, float y)
	{
		for (auto& element : m_Elements)
		{
			if (element->IsHidden())
			{
				continue;
			}

			if (element->InRange(x, y))
			{
				Update();
				return true;
			}
		}

		return false;
	}

	void UIPopup::Build()
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

	glm::vec3& UIPopup::GetColour()
	{
		return m_Elements.front()->GetColour();
	}

	bool UIPopup::IsMouseDown()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
				return true;
		}

		return false;
	}

}