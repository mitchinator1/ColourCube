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
	CONTINUE,
	LOAD,
	SAVE,
	TOGGLE
};

namespace UI
{
	struct UIHitBox
	{
		ACTION Action;
		float xMin, yMin, xMax, yMax;

		UIHitBox(ACTION inAction, float inXMin, float inYMin, float inXMax, float inYMax)
			: Action(inAction)
			, xMin(inXMin / 50.0f - 1.0f), yMin(inYMin / 50.0f - 1.0f)
			, xMax(inXMax / 50.0f - 1.0f), yMax(inYMax / 50.0f - 1.0f)
		{
			
		}

		~UIHitBox()	{ }
	};
}

#endif