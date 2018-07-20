#include "UIMaster.h"
#include "../Display.h"
#include "Font/FontType.h"
#include "../Input/UIMousePicker.h"
#include "UIBuilder.h"
#include "Element/UIButton.h"
#include "Element/UIDropdown.h"
#include "Element/UISlider.h"
#include "../Mesh/Mesh.h"

namespace UI
{
	UIMaster::UIMaster(std::shared_ptr<Display>& display)
		: m_Display(display), m_UpdateNeeded(false), m_Mouse(nullptr)
		, m_Action(ACTION::NONE), m_ElementsMesh(nullptr)
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

	bool UIMaster::HandleEvents(std::shared_ptr<Display> display)
	{
		bool event = false;
		m_Action = ACTION::NONE;

		if (m_Mouse)
		{
			//TODO: Add Keyboard shortcuts
			event = m_Mouse->HandleEvents(this);
		}
		return event;
	}

	void UIMaster::Update()
	{
		if (m_UpdateNeeded)
		{
			m_UpdateNeeded = false;

			HandleElements();
			
			HandleTexts();

			HandleMesh();
		}

		Continue();
	}

	void UIMaster::Continue()
	{
		if (m_Action != ACTION::CONTINUE)
			return;

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
		if (id.empty())
			return;

		for (auto& element : m_Elements)
		{
			if (element->GetID() == "Alert")
			{
				element->GetText()->SetKey(id + "Alert");
				if (id.find("Toggle") != std::string::npos)
				{
					element->GetText()->SetKeyNumber(element->GetText()->GetKeyNumber() ? 0 : 1);
				}
				else
				{
					element->GetText()->SetKeyNumber(0);
				}
				
				element->Reveal(std::string("Alert"));

				m_UpdateNeeded = true;
			}
		}

		for (auto& element : m_Elements)
		{			
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

	glm::vec3 UIMaster::GetColour()
	{
		for (auto& element : m_Elements)
		{
			if (element->GetID() == "ColourChooser")
				return glm::vec3(element->GetColour());
		}
		return glm::vec3(m_Elements.back()->GetColour());
	}

	Mesh* UIMaster::GetElementMesh()
	{
		return m_ElementsMesh.get();
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

	void UIMaster::HandleElements()
	{
		for (auto& element : m_Elements)
		{
			GrabTexts(element);
		}

		for (auto& element : m_Elements)
		{
			if (!element->UpdateNeeded() || element->IsHidden())
			{
				continue;
			}
			m_UpdateNeeded = true;
			element->Update();
		}
	}

	void UIMaster::HandleTexts()
	{
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

	void UIMaster::HandleMesh()
	{
		//TODO: set updates to only happen once, instead of twice
		std::vector<float> vertices;
		for (auto& element : m_Elements)
		{
			if (element->IsHidden())
				continue;
			element->UpdateFinished();

			auto newVertices = element->GetVertices();
			vertices.insert(vertices.end(), newVertices.begin(), newVertices.end());
		}
		std::vector<unsigned int> strides = { 3, 4 };
		//TODO: Update, instead of replace, Mesh
		m_ElementsMesh = std::make_unique<Mesh>(vertices, strides);
	}

}
