#include "UIMaster.h"
#include "../Display.h"
#include "Font/FontType.h"
#include "../Input/UIMousePicker.h"
#include "UIBuilder.h"
#include "Element/UIButton.h"
#include "Element/UIDropdown.h"
#include "Element/UISlider.h"
#include "Element/UIScrollbox.h"
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
		m_Elements.clear();
		m_Texts.clear();

		m_ElementsMesh.reset();
		m_FontMeshes.clear();

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
		auto& fontName = text->GetFont();

		text->Added();
		
		for (auto& font : m_Texts)
		{
			if (font.first->GetName() == fontName)
			{
				font.second.emplace_back(text);
				return;
			}
		}
		FontList newFont = { std::make_shared<Text::FontType>(fontName), std::vector<std::shared_ptr<UIText>>{ text } };
		m_Texts.emplace_back(newFont);
	}

	bool UIMaster::HandleEvents(std::shared_ptr<Display> display)
	{
		bool event = false;
		m_Action = ACTION::NONE;

		if (m_Mouse)
		{
			event = m_Mouse->HandleEvents(this);
		}
		//TODO: Add Keyboard shortcuts
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

		for (auto& font : m_Texts)
		{
			for (auto& text : font.second)
			{
				if (!text->Continue())
				{
					text->Remove();
					m_UpdateNeeded = true;
				}
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
		if (action != ACTION::NONE)
		{
			m_UpdateNeeded = true;
		}
	}

	void UIMaster::SetID(const std::string& id)
	{
		m_ID = id;
		if (!id.empty())
		{
			m_UpdateNeeded = true;
		}
	}

	glm::vec3 UIMaster::GetColour()
	{
		auto colour = glm::vec3{ 0.0f, 0.0f, 0.0f };

		for (auto& element : m_Elements)
		{
			if (element->GetParentID() == "ColourChooser")
			{
				colour = glm::vec3(element->GetColour());
			}
		}
		std::cout << "adding colour\n";
		//Add colour to ColourPalette
		for (auto& element : m_Elements)
		{
			//TODO: Not grabbing palette, but instead grabbing button
			//Link IDs on update. ex. get colour from colourchooser by link, show popup from link. 
			//This keeps function calls within UIMaster, instead of in the State.

			//if (element->GetParentID() == "ColourPalette")
			if (element->GetParentID() == "TestBox")
			{
				auto e = std::make_unique<UI::UIElement>();
				e->GetPosition().x = element->GetPosition().x + 5.0f;
				e->xSize = 15.0f;
				e->GetPosition().y = element->GetPosition().y + 5.0f;
				e->ySize = 20.0f;
				e->GetPosition().z -= 0.5f;
				e->colour.r = 1.0f;
				e->colour.g = 0.5f;
				e->colour.b = 0.7f;
				if (element->IsHidden())
					e->Hide();
				element->AddElement(e);
				//element->Build();
				break;
			}
		}

		m_UpdateNeeded = true;
		return colour;
	}

	Mesh* UIMaster::GetElementMesh()
	{
		return m_ElementsMesh.get();
	}

	std::vector<std::unique_ptr<Mesh>>& UIMaster::GetFontMeshes()
	{
		return m_FontMeshes;
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
			if (!element->UpdateNeeded())
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
			for (auto& text = font.second.begin(); text != font.second.end();)
			{

				if (!text->get()->isCreated())
				{
					text->get()->CreateMesh(font.first);
				}

				if (text->get()->UpdateNeeded())
				{
					text->get()->Update();
					m_UpdateNeeded = true;
				}

				if (text->get()->RemovalNeeded())
				{
					text = font.second.erase(text);
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
		if (!m_UpdateNeeded)
			return;

		std::vector<float> vertices;
		for (auto& element : m_Elements)
		{
			if (element->IsHidden())
				continue;
			element->UpdateFinished();

			auto newVertices = element->GetVertices();
			vertices.insert(vertices.end(), newVertices.begin(), newVertices.end());
		}

		if (!m_ElementsMesh)
		{
			std::vector<unsigned int> strides = { 3, 4 };
			m_ElementsMesh = std::make_unique<Mesh>(vertices, strides);
		}
		else
		{
			m_ElementsMesh->UpdateVertices(vertices, 7);
		}

		unsigned int index = 0;
		for (auto& font : m_Texts)
		{
			vertices.clear();
			if (font.second.empty())
				continue;

			for (auto& text : font.second)
			{
				if (text->IsHidden())
					continue;

				auto newVertices = text->GetVertices();
				vertices.insert(vertices.end(), newVertices.begin(), newVertices.end());
			}

			if (m_FontMeshes.size() <= index)
			{
				std::vector<unsigned int> strides = { 3, 2, 3 };
				m_FontMeshes.emplace_back(std::make_unique<Mesh>(vertices, strides));
				m_FontMeshes.back()->SetTexture(font.first->GetTexture());
			}
			else
			{
				m_FontMeshes[index]->UpdateVertices(vertices, 8);
			}
			++index;
		}
	}

}
