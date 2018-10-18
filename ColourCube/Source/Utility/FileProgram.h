#ifndef FILE_PROGRAM_H
#define FILE_PROGRAM_H
#include <string>
#include <unordered_map>
#include <fstream>

namespace Utility
{
	class FileProgram
	{
	private:
		std::ifstream m_Stream;
		std::string m_CurrentLine;

	protected:
		std::unordered_map<std::string, std::string> m_Values;

	public:
		FileProgram(const std::string& filepath);
		~FileProgram();

		bool LoadFile();
		bool LoadLine();

		auto& GetValues() { return m_Values; }

	protected:
		void ClearValueCache();

	private:
		void InsertValues(std::string& v1, std::string& v2);
		void TrimLeadingSpace(std::string& value, const char* t = " \t\n\r\f\v");

	};
}

#endif