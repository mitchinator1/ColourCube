#include "UIButton.h"
#include <iostream>
namespace UI
{
	UIButton::UIButton(float x, float y, float xSize, float ySize, glm::vec3 colour)
		: m_X(x), m_Y(y), m_XSize(xSize), m_YSize(ySize), m_Colour(colour)
		//, m_Background(x, y, xSize, ySize, colour)
	{
		
	}

	UIButton::~UIButton()
	{

	}

}