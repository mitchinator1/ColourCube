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

		//TODO: Make one function, with room for additional traits
		std::shared_ptr<UIElement>	BuildElement();
		std::shared_ptr<UIButton>	BuildButton();
		std::shared_ptr<UIDropdown> BuildDropdown();
		std::shared_ptr<UIElement>	BuildPopup();
		std::shared_ptr<UIElement>	BuildScrollbox();
		std::shared_ptr<UISlider>	BuildSlider();
		std::shared_ptr<UIText>		BuildText();

		ACTION StringToEnum(const std::string& value);

	};
}

#endif