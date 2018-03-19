#pragma once
#include <vector>
#include "Word.h"

namespace Text
{
	class Line {
	private:
		float m_MaxLength;
		float m_SpaceSize;

		std::vector<Word> m_Words;
		float m_CurrentLineLength = 0;

	public:
		Line(float spaceWidth, float fontSize, float maxLength);

		bool AttemptToAddWord(Word& word);
		float GetMaxLength();
		float GetLineLength();
		std::vector<Word>& GetWords();
	};
}