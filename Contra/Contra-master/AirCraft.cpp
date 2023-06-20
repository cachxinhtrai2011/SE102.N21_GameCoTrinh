#include "AirCraft.h"

void CAirCraft::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 25;
	bottom = top - 15;
}