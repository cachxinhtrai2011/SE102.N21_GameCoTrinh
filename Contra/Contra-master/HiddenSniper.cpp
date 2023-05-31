#include "HiddenSniper.h"
#include "Bill.h"

extern CBill* bill;
void CHiddenSniper::Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject)
{
	if (bill->GetX() < x)
		faceDirection = -1;
	else
		faceDirection = 1;
	if (abs(bill->GetX() - x) <= 100 && state == SNIPER_STATE_HIDDEN)
		SetState(SNIPER_STATE_SHOT);
	if (abs(bill->GetX() - x) > 100 && state == SNIPER_STATE_SHOT)
		SetState(SNIPER_STATE_HIDDEN);
}

void CHiddenSniper::Render()
{
	int aniID = -1;
	if (faceDirection == -1)
	{
		if (state == SNIPER_STATE_HIDDEN)
			aniID = ID_ANI_SNIPER_HIDDEN;
		else
			aniID = ID_ANI_SNIPER_HIDDEN_SHOT;
	}
	else
	{
		if (state == SNIPER_STATE_HIDDEN)
			aniID = ID_ANI_SNIPER_HIDDEN_RIGHT;
		else
			aniID = ID_ANI_SNIPER_HIDDEN_SHOT_RIGHT;
	}
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
}

void CHiddenSniper::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (state == SNIPER_STATE_HIDDEN)
	{
		right = x + 7;
		bottom = y + 38;
	}
	else
	{
		right = x + 23;
		bottom = y + 38;
	}
}

void CHiddenSniper::SetState(int state)
{
	if (state == SNIPER_STATE_SHOT)
		CAnimations::GetInstance()->Get(ID_ANI_SNIPER_HIDDEN_SHOT)->SetStartAnimation(CAnimations::GetInstance()->Get(ID_ANI_SNIPER_SHOW));
	if (state == SNIPER_STATE_HIDDEN)
		CAnimations::GetInstance()->Get(ID_ANI_SNIPER_HIDDEN)->SetStartAnimation(CAnimations::GetInstance()->Get(ID_ANI_SNIPER_SHOW));
	CGameObject::SetState(state);
}


