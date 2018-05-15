#ifndef UI_BUILDER_H
#define UI_BUILDER_H
#include <string>
#include <fstream>

namespace UI
{
	class UIMaster;
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
		void BuildText(UIMaster* ui);
		void BuildElement(UIMaster* ui);
	};
}

#endif