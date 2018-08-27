#include "TextLoader.h"
#include <fstream>
#include <sstream>

namespace Text
{
	std::string LoadString(const std::string& key)
	{
		std::ifstream stream("Resources/Text/EN.text");
		std::string line;
		while (std::getline(stream, line))
		{
			if (line.find(key) != std::string::npos)
			{
				std::istringstream part(line);
				std::getline(part, line, '"');
				stream >> line;
				std::getline(part, line, '"');
				return line;
			}
			if (stream.peek() == EOF)
				return "";
		}
		return "";
	}
}