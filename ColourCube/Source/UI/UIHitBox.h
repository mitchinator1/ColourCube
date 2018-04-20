#ifndef UI_HIT_BOX_H
#define UI_HIT_BOX_H

enum class ACTION
{
	NONE,
	PLAY,
	EDITOR,
	SETTINGS,
	EXIT,
	MENU,
	CONTINUE
};

namespace UI
{
	struct UIHitBox
	{
		ACTION Action;
		float xMin, yMin, xMax, yMax;

		UIHitBox(ACTION inAction, float inXMin, float inYMin, float inXMax, float inYMax)
			: Action(inAction), xMin(inXMin), yMin(inYMin), xMax(inXMax), yMax(inYMax)
		{
			
		}

		~UIHitBox()	{ }
	};
}

#endif