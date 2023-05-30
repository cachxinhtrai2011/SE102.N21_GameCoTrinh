#include "Canon.h"
#include "Bill.h"
#include "Utils.h"
extern CBill* bill;
void CCanon::Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject)
{
	if (state == CANON_STATE_NORMAL)
	{
		if (GetTickCount64() - lastTurn > CANON_ROTATION_DELAY && lastTurn != -1)
		{
			lastTurn = GetTickCount64();
			float left, top, down, right;
			bill->GetBoundingBox(left, top, down, right);
			float billWidth = right - left;
			float billHeight = down - top;
			radius = Radius(left + billWidth, top + billHeight, x + 16, y + 16);
		}
	}
	if (abs(bill->GetX() - x) <= 200 && state == CANON_STATE_HIDDEN)
		this->SetState(CANON_STATE_NORMAL);
}

void CCanon::Render()
{
	int aniID = -1;
	if (state == CANON_STATE_NORMAL)
		if (radius > PI / 6 && radius < PI / 4)
			aniID = ID_ANI_CANON_NORMAL_1;
		else if (radius >= PI / 4 && radius < PI / 2)
			aniID = ID_ANI_CANON_NORMAL_2;
		else aniID = ID_ANI_CANON_NORMAL;
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
}

void CCanon::LoadAnimation()
{
	CTextures* texture = CTextures::GetInstance();
	texture->Add(TEXTURE_CANON_ID, L"./Resources/Images/Cannon_all.png");
	CAnimations* animations = CAnimations::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	sprites->Add(ID_ANI_CANON_NORMAL, 66, 2, 98, 34, texture->Get(TEXTURE_CANON_ID));
	
	LPANIMATION ani = new CAnimation();
	ani->Add(ID_ANI_CANON_NORMAL);
	animations->Add(ID_ANI_CANON_NORMAL, ani);

	sprites->Add(ID_ANI_CANON_NORMAL_1, 98, 2, 130, 34, texture->Get(TEXTURE_CANON_ID));

	ani = new CAnimation();
	ani->Add(ID_ANI_CANON_NORMAL_1);
	animations->Add(ID_ANI_CANON_NORMAL_1, ani);

	sprites->Add(ID_ANI_CANON_NORMAL_2, 130, 2, 162, 98, texture->Get(TEXTURE_CANON_ID));
	ani = new CAnimation();
	ani->Add(ID_ANI_CANON_NORMAL_2);
	animations->Add(ID_ANI_CANON_NORMAL_2, ani);

	sprites->Add(ID_ANI_CANON_HIDDEN, 2, 2, 34, 34, texture->Get(TEXTURE_CANON_ID));
	sprites->Add(ID_ANI_CANON_HIDDEN + 1, 34, 2, 66, 34, texture->Get(TEXTURE_CANON_ID));
	ani = new CAnimation();
	ani->Add(ID_ANI_CANON_HIDDEN);
	ani->Add(ID_ANI_CANON_HIDDEN + 1);
	ani->oneTimeAnimation = true;
	animations->Add(ID_ANI_CANON_HIDDEN, ani);
}

void CCanon::SetState(int state)
{
	if (state == CANON_STATE_NORMAL)
		CAnimations::GetInstance()->Get(ID_ANI_CANON_NORMAL)->SetStartAnimation(CAnimations::GetInstance()->Get(ID_ANI_CANON_HIDDEN));
	CGameObject::SetState(state);
}

void CCanon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 32;
	bottom = y + 32;
}
