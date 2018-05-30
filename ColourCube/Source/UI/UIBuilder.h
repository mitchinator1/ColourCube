#ifndef UI_BUILDER_H
#define UI_BUILDER_H
#include <string>
#include <fstream>

namespace UI
{
	class UIMaster;
	class UIElement;
	class UIButton;
	class UIDropdown;
	class UIText;

	class UIBuilder
	{
	private:
		std::fstream m_Stream;
		std::string m_Filepath;

	public:
		UIBuilder(const std::string& filename);
		~UIBuilder();

		void LoadUI(UIMaster* ui);

	private:
		std::unique_ptr<UIButton>	BuildButton();
		std::unique_ptr<UIDropdown> BuildDropdown();
		std::shared_ptr<UIText>		BuildText();
		std::unique_ptr<UIElement>	BuildPopup();
		std::unique_ptr<UIButton>	BuildSlider();
		std::unique_ptr<UIElement>	BuildElement(const std::string& type);

	};
}

#endif