#pragma once
#include "Sniper.h"
class CHiddenSniper: public CSniper
{
public:
	CHiddenSniper(float x, float y) : CSniper(x, y) { state = SNIPER_STATE_HIDDEN; };
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
};

