#include "Line.h"

namespace Text
{
	Line::Line(float spaceWidth, float fontSize, float maxLength)
		: m_SpaceSize(spaceWidth * fontSize), m_MaxLength(maxLength)
	{

	}

	bool Line::AttemptToAddWord(Word& word)
	{
		float additionalLength = word.GetWidth();
		additionalLength += !m_Words.empty() ? m_SpaceSize : 0.0f;
		if (m_CurrentLineLength + additionalLength <= m_MaxLength)
		{
			m_Words.emplace_back(word);
			m_CurrentLineLength += additionalLength;
			return true;
		}
		return false;
	}

	float Line::GetMaxLength()
	{
		return m_MaxLength;
	}

	float Line::GetLineLength()
	{
		return m_CurrentLineLength;
	}

	std::vector<Word>& Line::GetWords()
	{
		return m_Words;
	}
}