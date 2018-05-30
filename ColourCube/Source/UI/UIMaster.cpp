#include "UIMaster.h"
#include "../Display.h"
#include "Font/FontType.h"
#include "UITextBox.h"
#include "UIBuilder.h"
#include "../Input/UIMousePicker.h"
#include "UIButton.h"
#include "UIDropdown.h"

namespace UI
{
	UIMaster::UIMaster() noexcept
		: m_UpdateNeeded(false), m_Mouse(nullptr)
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
			m_Mouse = std::make_unique<Input::UIMousePicker>();
		}
		Update();
	}

	void UIMaster::AddElement(TYPE type, std::unique_ptr<UIElement>& element)
	{
		m_UpdateNeeded = true;
		m_Elements[type].emplace_back(std::move(element));
	}

	void UIMaster::AddElement(const std::string& type, std::unique_ptr<UIElement>& element)
	{
		m_UpdateNeeded = true;
		m_Elements[StringToEnum(type)].emplace_back(std::move(element));
	}

	void UIMaster::AddElement(TYPE type, std::unique_ptr<UIButton>& element)
	{
		m_UpdateNeeded = true;
		m_Elements[type].emplace_back(std::move(element));
	}

	void UIMaster::AddElement(const std::string& type, std::unique_ptr<UIButton>& element)
	{
		m_UpdateNeeded = true;
		m_Elements[StringToEnum(type)].emplace_back(std::move(element));
	}

	void UIMaster::AddElement(TYPE type, std::unique_ptr<UIDropdown>& element)
	{
		m_UpdateNeeded = true;
		m_Elements[type].emplace_back(std::move(element));
	}
	
	void UIMaster::AddElement(const std::string& type, std::unique_ptr<UIDropdown>& element)
	{
		m_UpdateNeeded = true;
		m_Elements[StringToEnum(type)].emplace_back(std::move(element));
	}
	
	std::shared_ptr<UIText>& UIMaster::AddText(const std::string& fontName, const std::string& key)
	{
		m_UpdateNeeded = true;

		if (m_Texts.find(fontName) != m_Texts.end())
		{
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>());
			m_Texts[fontName].second.back()->SetKey(key);
		}
		else
		{
			m_Texts[fontName].first = std::make_unique<Text::FontType>(fontName);
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>());
			m_Texts[fontName].second.back()->SetKey(key);
		}
		return m_Texts[fontName].second.back();
	}

	void UIMaster::AddText(const std::string& fontName, std::shared_ptr<UIText> text)
	{
		m_UpdateNeeded = true;

		if (m_Texts.find(fontName) != m_Texts.end())
		{
			m_Texts[fontName].second.emplace_back(std::move(text));
		}
		else
		{
			m_Texts[fontName].first = std::make_unique<Text::FontType>(fontName);
			m_Texts[fontName].second.emplace_back(std::move(text));
		}
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
			m_Mouse->HandleEvents(display);

			m_Mouse->CheckMouseOver(m_Elements[TYPE::BUTTON]);
			//m_Mouse->HighlightElement(m_Elements[TYPE::TEXTBOX]);

			if (m_Mouse->IsToggled())
			{
				m_Action = m_Mouse->GetMouseDown(m_Elements[TYPE::BUTTON]);
			}
			/*if (m_Mouse->IsHeld())
				if (m_Mouse->MoveElement(m_Elements[TYPE::SLIDER]))
					m_UpdateNeeded = true;*/
		}
	}

	void UIMaster::Update()
	{
		if (m_UpdateNeeded)
		{
			m_UpdateNeeded = false;

			for (auto& elements : m_Elements)
			{
				GrabTexts(elements.second);
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
				m_Elements[TYPE::TEXTBOX].clear();
				m_UpdateNeeded = true;
			}
		}
	}

	glm::vec3& UIMaster::GetColour()
	{
		return m_Elements[TYPE::POPUP].back()->colour;
	}

	TYPE UIMaster::StringToEnum(const std::string& text)
	{
		if (text == "button")		return TYPE::BUTTON;
		if (text == "background")	return TYPE::BACKGROUND;
		if (text == "popup")		return TYPE::POPUP;
		if (text == "slider")		return TYPE::SLIDER;
		if (text == "textbox")		return TYPE::TEXTBOX;

		return TYPE::BACKGROUND;
	}

	void UIMaster::GrabTexts(std::vector<std::unique_ptr<UIElement>>& elements)
	{
		for (auto& element : elements)
		{
			if (element->GetText() != nullptr)
			{
				if (!element->GetText()->IsAdded())
				{
					AddText(element->GetText());
				}
			}

			GrabTexts(element->GetElements());
		}
	}

}
