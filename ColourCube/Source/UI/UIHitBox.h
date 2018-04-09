#ifndef UI_HIT_BOX_H
#define UI_HIT_BOX_H

namespace UI
{
	struct UIHitBox
	{
		float xMin, yMin, xMax, yMax;
		unsigned int ID;

		UIHitBox(float inXMin, float inYMin, float inXMax, float inYMax, unsigned int inID)
			: xMin(inXMin), yMin(inYMin), xMax(inXMax), yMax(inYMax), ID(inID)
		{
			
		}
	};
}

#endif