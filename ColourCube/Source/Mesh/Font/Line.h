#pragma once
#include <vector>
#include "Word.h"

class Line {
private:
	float m_MaxLength;
	float m_SpaceSize;

	std::vector<Word> m_Words;
	float m_CurrentLineLength = 0;

public:
	Line(float spaceWidth, float fontSize, float maxLength)
	: m_SpaceSize(spaceWidth * fontSize), m_MaxLength(maxLength)
	{

	}

	bool AttemptToAddWord(Word& word)
	{
		float additionalLength = word.GetWidth();
		additionalLength += !m_Words.empty() ? m_SpaceSize : 0;
		if (m_CurrentLineLength + additionalLength <= m_MaxLength)
		{
			m_Words.emplace_back(word);
			m_CurrentLineLength += additionalLength;
			return true;
		}
		else
		{
			return false;
		}
	}

	float GetMaxLength()
	{
		return m_MaxLength;
	}

	float GetLineLength()
	{
		return m_CurrentLineLength;
	}

	std::vector<Word>& GetWords()
	{
		return m_Words;
	}

};