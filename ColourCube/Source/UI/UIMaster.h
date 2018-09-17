#ifndef UI_MASTER_H
#define UI_MASTER_H
#include <unordered_map>
#include "Element/UIElement.h"

#include <iostream>

struct Display;
namespace Text { class FontType; }
namespace Input { class UIMousePicker; }
class Mesh;

namespace UI
{
	class Element;
	typedef std::pair<std::shared_ptr<Text::FontType>, std::vector<std::shared_ptr<UIText>>> FontList;

	class UIMaster
	{
	private:
		bool m_UpdateNeeded;
		ACTION m_Action;
		std::string m_ID = "";
		unsigned int m_CurrentLevel;
		std::vector<std::unique_ptr<UIElement>> m_Elements;
		std::vector<FontList> m_Texts;

		std::unique_ptr<Input::UIMousePicker> m_Mouse;
		std::shared_ptr<Display> m_Display;

		std::unique_ptr<Mesh> m_ElementsMesh;
		std::vector<std::unique_ptr<Mesh>> m_FontMeshes;

	public:
		UIMaster(std::shared_ptr<Display>& display);
		~UIMaster();

		void Build(const std::string& state);

		void AddText(std::shared_ptr<UIText>& text);

		bool HandleEvents(std::shared_ptr<Display> display); 
		void Update();
		void Continue();
		void Reveal(const std::string& id);

		void SetAction(ACTION action);
		void SetID(const std::string& id);

		glm::vec3 GetColour();
		Mesh* GetElementMesh();
		std::vector<std::unique_ptr<Mesh>>& GetFontMeshes();

		void ForceUpdate()			{ m_UpdateNeeded = true; }
		auto& GetID()				{ return m_ID; }
		auto& GetLevelNumber()		{ return m_CurrentLevel; }
		inline auto& GetElements()	{ return m_Elements; }
		inline auto& GetTexts()		{ return m_Texts; }
		inline auto GetAction()		{ return m_Action; }

	private:
		void GrabTexts(std::unique_ptr<UIElement>& element);
		void HandleElements();
		void HandleTexts();
		void HandleMesh();
		
	public:
		template <typename T>
		void AddElement(std::unique_ptr<T>& element)
		{
			m_UpdateNeeded = true;
			m_Elements.emplace_back(std::move(element));

			//TODO: Check other IDs and match with them.
			//m_Elements can only have one or none of the ID when the new one is added.
			//So if theres a match in m_Elements, it can only be the pair, not element, since element hasn't been added yet.
			//Find a way to link what's needed (hide, get colour, id, etc.)

			/*for (auto e = m_Elements.begin(); e != m_Elements.end() - 1;)
			{
				auto& id = e->get()->GetID();
				
				if (id == "")
				{
					++e;
					continue;
				}

				if (id == m_Elements.back()->GetID())
				{
					e->get()->
					std::cout << id << '\n';
					break;
				}
				++e;
			}*/
		}

	};
}

#endif