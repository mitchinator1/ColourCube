#ifndef MOUSE_2D_H
#define MOUSE_2D_H
#include "MouseBase.h"

namespace Input
{
	class Mouse2D : public MouseBase
	{
	public:
		Mouse2D(std::shared_ptr<Display>& display);
		virtual ~Mouse2D();
	};
}

#endif