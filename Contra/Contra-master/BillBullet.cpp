#include "BillBullet.h"
#include "Soldier.h"


void CBillBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject)
{
	CBullet::Update(dt, gameObject);
}

void CBillBullet::LoadAnimation()
{
LPTEXTURE texture = CTextures::GetInstance()->Get(ID_BULLET_TEXTURE);
if (texture == NULL)
{
	CBullet::LoadAnimation();
	texture = CTextures::GetInstance()->Get(ID_BULLET_TEXTURE);
}
CSprites* sprites = CSprites::GetInstance();
sprites->Add(ID_ANI_BULLET_NORMAL, 69, 28, 73, 32, texture);
LPANIMATION ani = new  CAnimation(100);
ani->Add(ID_ANI_BULLET_NORMAL);
CAnimations::GetInstance()->Add(ID_ANI_BULLET_NORMAL, ani);
}

void CBillBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 4;
	bottom = y - 4;
}

void CBillBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CSoldier*>(e->obj))
		OnCollisionWithSoldier(e);
}


void CBillBullet::OnCollisionWithSoldier(LPCOLLISIONEVENT e)
{
	CSoldier* soldier = dynamic_cast<CSoldier*>(e->obj);

	if (e->nx < 0)
	{
		if (soldier->GetState() != SOLDIER_STATE_DEATH)
		{
			soldier->SetState(SOLDIER_STATE_DEATH);
		}
	}
}
