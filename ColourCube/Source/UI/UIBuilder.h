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
	class UISlider;
	class UIText;
	enum class ACTION;

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
		std::unique_ptr<UIElement>	BuildElement();
		std::unique_ptr<UIButton>	BuildButton();
		std::unique_ptr<UIDropdown> BuildDropdown();
		std::unique_ptr<UIElement>	BuildPopup();
		std::unique_ptr<UIElement>	BuildScrollbox();
		std::unique_ptr<UISlider>	BuildSlider();
		std::shared_ptr<UIText>		BuildText();

		ACTION StringToEnum(const std::string& value);

	};
}

#endif