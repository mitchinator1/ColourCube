#include "UIBuilder.h"
#include <iostream>
#include "UIMaster.h"
#include "UITextBox.h"

namespace UI
{
	UIBuilder::UIBuilder(const std::string& filename)
	{
		m_Filepath = "Resources/Data/" + filename + ".xml";
	}

	UIBuilder::~UIBuilder()
	{

	}

	void UIBuilder::LoadUI(UIMaster* ui)
	{
		m_Stream.open(m_Filepath);
		std::string line;
		while (std::getline(m_Stream, line, ' '))
		{
			if (line.find("text") != std::string::npos)
			{
				BuildText(ui);
				continue;
			}

			if (line.find("element") != std::string::npos)
			{
				BuildElement(ui);
				continue;
			}

			std::getline(m_Stream, line, '<');
		}
		m_Stream.close();
	}

	void UIBuilder::BuildText(UIMaster* ui)
	{
		auto& text = std::make_unique<UIText>();


		std::string font;
		float x = 0.0f, y = 0.0f, size = 1.0f, r, g, b;
		bool center = false;

		std::string line;
		while (line != "/text")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

			if (line == "font")
			{
				std::getline(m_Stream, font, '<');
				continue;
			}

			if (line == "key")
			{
				std::string key;
				std::getline(m_Stream, key, '<');
				text->SetKey(key);
				continue;
			}

			if (line == "keynumber")
			{
				unsigned int number;
				m_Stream >> number;
				text->SetKeyNumber(number);
				continue;
			}

			if (line == "position")
			{
				m_Stream >> x >> y;
				text->SetPosition(x, y);
				continue;
			}

			if (line == "size")
			{
				m_Stream >> size;
				text->SetSize(size);
				continue;
			}

			if (line == "colour")
			{
				m_Stream >> r >> g >> b;
				text->SetColour(r, g, b);
			}

			if (line == "halign")
			{
				std::string align;
				std::getline(m_Stream, align, '<');
				if (align == "center")
				{
					text->SetCenter(true);
				}
				if (align == "left")
				{
					text->SetPosition(x, y);
				}
				continue;
			}
		}
		ui->AddText(font, std::move(text));
	}

	void UIBuilder::BuildElement(UIMaster* ui)
	{
		auto& element = std::make_unique<UIElement>();

		float minX = 0.0f, minY = 0.0f, maxX = 0.0f, maxY = 0.0f;
		float r = 1.0f, g = 1.0f, b = 1.0f;
		bool hidden = false;

		std::string line;
		std::getline(m_Stream, line, '\n');
		std::string type;
		if (line.find("type") != std::string::npos)
		{
			auto it = line.find('"');
			while (line[++it] != '"')
				type += line[it];
		}

		while (line != "/element")
		{
			std::getline(m_Stream, line, '<');
			std::getline(m_Stream, line, '>');

			if (line == "hidden")
			{
				std::string text;
				std::getline(m_Stream, text, '<');
				if (text == "true")
				{
					hidden = true;
					element->SetHidden(hidden);
				}
				continue;
			}

			if (line == "position")
			{
				m_Stream >> minX >> minY;
				element->SetMin(minX, minY);
				continue;
			}

			if (line == "size")
			{
				m_Stream >> maxX >> maxY;
				element->SetMax(maxX, maxY);
				continue;
			}

			if (line == "onMouseOver")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				element->SetMouseOver(action);
				continue;
			}

			if (line == "onMouseDown")
			{
				std::string action;
				std::getline(m_Stream, action, '<');
				element->SetMouseDown(action);
				continue;
			}

			if (line == "colour")
			{
				m_Stream >> r >> g >> b;
				element->SetColour(r, g, b);
				continue;
			}

			if (line == "depth")
			{
				float depth;
				m_Stream >> depth;
				element->SetDepth(depth);
				continue;
			}

			if (line == "alpha")
			{
				float alpha;
				m_Stream >> alpha;
				element->SetAlpha(alpha);
				continue;
			}

			if (line == "persistantalpha")
			{
				float alpha;
				m_Stream >> alpha;
				element->SetPersistantAlpha(alpha);
				continue;
			}

			if (line == "value")
			{
				float value;
				m_Stream >> value;
				element->SetWidth(maxX)
					->SetValue(value);
				continue;
			}

			if (line == "valuerange")
			{
				float min, max;
				m_Stream >> min >> max;
				element->SetValueRange(min, max);
				continue;
			}

			if (line.find("text") != std::string::npos)
			{
				auto& text = std::make_unique<UIText>();
				if (type == "textbox")
					text = std::make_unique<UITextBox>();
				text->SetPosition(minX, minY)
					->SetHidden(hidden);
				std::string font;
				while (line != "/text")
				{
					std::getline(m_Stream, line, '<');
					std::getline(m_Stream, line, '>');

					if (line == "font")
					{
						std::getline(m_Stream, font, '<');
						continue;
					}

					if (line == "key")
					{
						std::string key;
						std::getline(m_Stream, key, '<');
						text->SetKey(key);
						continue;
					}

					if (line == "keynumber")
					{
						unsigned int keyNumber;
						m_Stream >> keyNumber;
						text->SetKeyNumber(keyNumber);
						continue;
					}

					if (line == "size")
					{
						float size;
						m_Stream >> size;
						text->SetSize(size);
						continue;
					}

					if (line == "linesize")
					{
						float size;
						m_Stream >> size;
						text->SetLineSize(size);
						continue;
					}

					if (line == "colour")
					{
						float r, g, b;
						m_Stream >> r >> g >> b;
						text->SetColour(r, g, b);
						continue;
					}

					if (line == "indent")
					{
						float xIn, yIn;
						m_Stream >> xIn >> yIn;
						text->SetPosition(minX + xIn, minY + yIn);
						continue;
					}

					if (line == "halign")
					{
						std::string align;
						std::getline(m_Stream, align, '<');
						if (align == "center")
						{
							text->SetPosition((minX + (maxX / 2.0f)) - 50.0f, minY)
								->SetCenter(true);
						}
						if (align == "left")
						{
							text->SetPosition(minX - 8.0f, minY);
						}
						continue;
					}
				}

				ui->AddText(font, std::move(text));
			}

			if (line.find("slider") != std::string::npos)
			{
				while (line != "/slider")
				{
					std::getline(m_Stream, line, '<');
					std::getline(m_Stream, line, '>');

					if (line == "width")
					{
						float width;
						m_Stream >> width;
						element->SetWidth(maxX);
						element->SetMax(width, maxY);
						continue;
					}

					if (line == "depth")
					{
						float depth;
						m_Stream >> depth;
						element->SetDepth(depth);
						continue;
					}

				}
			}

			if (line.find("background") != std::string::npos)
			{
				auto& background = std::make_unique<UIElement>();
				background->SetMin(minX, minY)
					->SetColour(r, g, b)
					->SetHidden(hidden);
				while (line != "/background")
				{
					std::getline(m_Stream, line, '<');
					std::getline(m_Stream, line, '>');

					if (line == "thickness")
					{
						float thickness;
						m_Stream >> thickness;
						background->SetMin(minX, minY + (maxY / 2.0f) - thickness / 2.0f)
							->SetMax(maxX, thickness);
						continue;
					}

					if (line == "depth")
					{
						float depth;
						m_Stream >> depth;
						background->SetDepth(depth);
						continue;
					}

					if (line == "colour")
					{
						float r, g, b;
						m_Stream >> r >> g >> b;
						background->SetColour(r, g, b);
						continue;
					}
				}
				background->Build();
				ui->AddElement(TYPE::BACKGROUND, std::move(background));
			}

		}
		element->Build();
		ui->AddElement(type, std::move(element));
	}

}
