#include "UIMaster.h"
#include "../Display.h"
#include "Font/FontType.h"
#include "../Input/UIMousePicker.h"
#include "UIBuilder.h"
#include "Element/UIText.h"
#include "Element/UIButton.h"
#include "Element/UIDropdown.h"
#include "Element/UISlider.h"

namespace UI
{
	UIMaster::UIMaster(std::shared_ptr<Display>& display)
		: m_Display(display), m_UpdateNeeded(false), m_Mouse(nullptr)
		, m_Action(ACTION::NONE)
	{
		
	}

	UIMaster::~UIMaster()
	{

	}

	void UIMaster::Build(const std::string& state)
	{
		UIBuilder builder(state);
		builder.LoadUI(this);
		if (!m_Mouse)
		{
			m_Mouse = std::make_unique<Input::UIMousePicker>(m_Display);
		}
		Update();
	}

	void UIMaster::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_UpdateNeeded = true;
		m_Elements.emplace_back(std::move(element));
	}

	void UIMaster::AddElement(std::unique_ptr<UIButton>& element)
	{
		m_UpdateNeeded = true;
		m_Elements.emplace_back(std::move(element));
	}
	
	void UIMaster::AddElement(std::unique_ptr<UIDropdown>& element)
	{
		m_UpdateNeeded = true;
		m_Elements.emplace_back(std::move(element));
	}
	
	void UIMaster::AddElement(std::unique_ptr<UISlider>& element)
	{
		m_UpdateNeeded = true;
		m_Elements.emplace_back(std::move(element));
	}
	
	void UIMaster::AddText(std::shared_ptr<UIText>& text)
	{
		m_UpdateNeeded = true;
		auto& font = text->GetFont();

		if (m_Texts.find(font) != m_Texts.end())
		{
			m_Texts[font].second.emplace_back(text);
			text->Added();
		}
		else
		{
			m_Texts[font].first = std::make_unique<Text::FontType>(font);
			m_Texts[font].second.emplace_back(text);
			text->Added();
		}
	}

	void UIMaster::HandleEvents(std::shared_ptr<Display> display)
	{
		m_Action = ACTION::NONE;

		if (m_Mouse)
		{
			m_Mouse->HandleEvents(this);
		}
	}

	void UIMaster::Update()
	{
		if (m_UpdateNeeded)
		{
			m_UpdateNeeded = false;

			for (auto& element : m_Elements)
			{
				GrabTexts(element);
				
				if (element->UpdateNeeded())
				{
					element->Update();
					m_UpdateNeeded = true;
				}
			}

			for (auto& font : m_Texts)
			{
				for (auto& text = font.second.second.begin(); text != font.second.second.end();)
				{
					if (!text->get()->isCreated())
					{
						text->get()->CreateMesh(font.second.first.get());
					}
					if (text->get()->UpdateNeeded())
					{
						text->get()->Update();
						m_UpdateNeeded = true;
					}
					if (text->get()->RemovalNeeded())
					{
						text = font.second.second.erase(text);
					}
					else
					{
						++text;
					}
				}
			}
		}
	}

	void UIMaster::Continue()
	{
		for (auto& text : m_Texts["Arial"].second)
		{
			if (!text->Continue())
			{
				text->Remove();
				m_UpdateNeeded = true;
			}
		}
	}

	void UIMaster::Reveal(const std::string& id)
	{
		for (auto& element : m_Elements)
		{
			if (element->GetID() == id + "Alert")
			{
				element->Reveal(id + "Alert");

				m_UpdateNeeded = true;
			}
			
			if (element->GetID() == id)
			{
				element->Reveal(id);

				m_UpdateNeeded = true;
			}
		}
	}

	void UIMaster::SetAction(ACTION action)
	{
		m_Action = action;
	}

	void UIMaster::SetID(const std::string& id)
	{
		m_ID = id;
	}

	glm::vec3& UIMaster::GetColour()
	{
		for (auto& element : m_Elements)
		{
			if (element->GetID() == "ColourChooser")
				return element->GetColour();
		}
		return m_Elements.back()->GetColour();
	}

	void UIMaster::GrabTexts(std::unique_ptr<UIElement>& element)
	{
		if (element->GetText() != nullptr)
		{
			if (!element->GetText()->IsAdded())
			{
				AddText(element->GetText());
			}
		}

		for (auto& child : element->GetElements())
		{
			GrabTexts(child);
		}
	}

}
