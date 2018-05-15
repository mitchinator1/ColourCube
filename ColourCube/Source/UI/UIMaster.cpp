#include "UIMaster.h"
#include "../Display.h"
#include "Font/FontType.h"
#include "UITextBox.h"
#include "UIBuilder.h"
#include "../Input/UIMousePicker.h"

namespace UI
{
	UIMaster::UIMaster()
		: m_UpdateNeeded(false), m_MousePicker(nullptr)
	{

	}

	UIMaster::~UIMaster()
	{

	}

	void UIMaster::Build(const std::string& state)
	{
		UIBuilder builder(state);
		builder.LoadUI(this);
		if (!m_MousePicker)
		{
			m_MousePicker = std::make_unique<Input::UIMousePicker>();
		}
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
	
	std::unique_ptr<UIText>& UIMaster::AddText(const std::string& fontName, const std::string& key, float x, float y)
	{
		m_UpdateNeeded = true;

		if (m_Texts.find(fontName) != m_Texts.end())
		{
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>(key, x, y));
		}
		else
		{
			m_Texts[fontName].first = std::make_unique<Text::FontType>(fontName);
			m_Texts[fontName].second.emplace_back(std::make_unique<UIText>(key, x, y));
		}
		return m_Texts[fontName].second.back();
	}

	void UIMaster::AddText(const std::string& fontName, std::unique_ptr<UIText> text)
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

	void UIMaster::AddTextBox(const std::string& fontName, const std::string& key, unsigned int keyNumber)
	{
		std::unique_ptr<UITextBox> textBox = std::make_unique<UITextBox>(key, keyNumber);

		//AddElement(TYPE::TEXTBOX, textBox->GetBackground());
		AddText(fontName, std::move(textBox));

		m_UpdateNeeded = true;
	}

	void UIMaster::HandleEvents(std::shared_ptr<Display> display)
	{
		m_Action = ACTION::NONE;

		if (m_MousePicker)
		{
			m_MousePicker->HandleEvents(display);
			if (m_MousePicker->IsToggled())
			{
				m_Action = m_MousePicker->GetAction(m_Elements);
				if (m_Action != ACTION::NONE)
				{
					m_UpdateNeeded = true;
				}
				m_MousePicker->MoveElement(m_Elements[TYPE::SLIDER]);
				if (!m_Elements[TYPE::SLIDER].empty())
				{
					m_Elements[TYPE::COLOUR_CHOOSER].back()->SetColour(
						m_Elements[TYPE::SLIDER][0]->GetValue(),
						m_Elements[TYPE::SLIDER][1]->GetValue(),
						m_Elements[TYPE::SLIDER][2]->GetValue()
					);
				}
			}
			m_MousePicker->HighlightElement(m_Elements[TYPE::BUTTON]);
			m_MousePicker->HighlightElement(m_Elements[TYPE::TEXTBOX]);
		}
	}

	void UIMaster::Update()
	{
		if (m_UpdateNeeded)
		{
			m_UpdateNeeded = false;
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

	void UIMaster::Reveal()
	{
		for (auto& slider : m_Elements[UI::TYPE::SLIDER])
		{
			if (slider->IsHidden())
			{
				slider->SetHidden(false);
			}
		}
		for (auto& background : m_Elements[UI::TYPE::BACKGROUND])
		{
			if (background->IsHidden())
			{
				background->SetHidden(false);
			}
		}
		for (auto& text : m_Texts["Arial"].second)
		{
			if (text->IsHidden())
			{
				text->SetHidden(false);
			}
		}
	}

	TYPE UIMaster::StringToEnum(const std::string& text)
	{
		if (text == "button")			return TYPE::BUTTON;
		if (text == "background")		return TYPE::BACKGROUND;
		if (text == "colourchooser")	return TYPE::COLOUR_CHOOSER;
		if (text == "slider")			return TYPE::SLIDER;
		if (text == "textbox")			return TYPE::TEXTBOX;

		return TYPE::BACKGROUND;
	}

}
