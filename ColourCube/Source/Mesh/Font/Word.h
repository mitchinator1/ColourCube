#pragma once
#include <vector>
#include "Character.h"

class Word {
private:
	std::vector<Character> m_Characters;
	float m_Width = 0;
	float m_FontSize;

public:
	Word(float fontSize)
		: m_FontSize(fontSize)
	{

	}

	void AddCharacter(Character& character)
	{
		m_Characters.emplace_back(character);
		m_Width += character.xAdvance * m_FontSize;
	}

	std::vector<Character>& GetCharacters()
	{
		return m_Characters;
	}

	float GetWidth()
	{
		return m_Width;
	}

};
