#include "RockFall.h"
#include "Bill.h"

extern CBill* bill;
void CRockFall::Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject)
{
	x += vx * dt;
	y += vy * dt;
	if (x - 10 <= bill->GetX() && bill->GetX() <= x + 10 && state == ROCKFALL_STATE_IDLE)
		SetState(ROCKFALL_STATE_SHAKING);
	else if (state == ROCKFALL_STATE_SHAKING)
	{
		shakeTime--;
		vx = -vx;
		if (shakeTime == 0)
			this->SetState(ROCKFALL_STATE_FALL);
	}
}

void CRockFall::Render()
{
	if (state == ROCKFALL_STATE_IDLE)
		CAnimations::GetInstance()->Get(ID_ANI_ROCKFALL_STAY)->Render(x, y);
	else if (state == ROCKFALL_STATE_SHAKING)
	{
		CAnimations::GetInstance()->Get(ID_ANI_ROCKFALL_STAY)->Render(x, y);
	}
	else if (state == ROCKFALL_STATE_FALL)
		CAnimations::GetInstance()->Get(ID_ANI_ROCKFALL_FALL)->Render(x, y);
}

void CRockFall::LoadAnimation()
{
	CTextures* textures = CTextures::GetInstance();
	textures->Add(TEXTURE_ROCKFALL_ID, L"./Resources/Images/rockfall.png");
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	sprites->Add(ID_ANI_ROCKFALL_STAY, 5, 2, 28, 28, textures->Get(TEXTURE_ROCKFALL_ID));
	LPANIMATION ani = new CAnimation(100);
	ani->Add(ID_ANI_ROCKFALL_STAY);
	animations->Add(ID_ANI_ROCKFALL_STAY, ani);

	sprites->Add(ID_ANI_ROCKFALL_FALL, 5, 2, 28, 28, textures->Get(TEXTURE_ROCKFALL_ID));
	sprites->Add(ID_ANI_ROCKFALL_FALL + 1, 35, 4, 61, 27, textures->Get(TEXTURE_ROCKFALL_ID));
	sprites->Add(ID_ANI_ROCKFALL_FALL + 2, 69, 2, 92, 28, textures->Get(TEXTURE_ROCKFALL_ID));
	sprites->Add(ID_ANI_ROCKFALL_FALL + 3, 99, 4, 125, 27, textures->Get(TEXTURE_ROCKFALL_ID));

	ani = new CAnimation(100);

	ani->Add(ID_ANI_ROCKFALL_FALL);
	ani->Add(ID_ANI_ROCKFALL_FALL + 1);
	ani->Add(ID_ANI_ROCKFALL_FALL + 2);
	ani->Add(ID_ANI_ROCKFALL_FALL + 3);

	animations->Add(ID_ANI_ROCKFALL_FALL, ani);
}

void CRockFall::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

void CRockFall::OnNoCollision(DWORD dt)
{
}

void CRockFall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 26;
	bottom = y + 26;
}

void CRockFall::SetState(int state)
{
	if (state == ROCKFALL_STATE_SHAKING)
	{
		vx = 0.5f;
	}
	else if (state == ROCKFALL_STATE_FALL)
	{
		vx = 0;
		vy = FALL_SPEED;
	}
	CGameObject::SetState(state);
}
