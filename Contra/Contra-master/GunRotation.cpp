#include "GunRotation.h"
#include "Bill.h"
#include "RifleBullet.h"
#include "Utils.h"
extern CBill* bill;
#define GUN_RECOIL_TIME 3000
void CGunRotation::Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject)
{
	CCollision::GetInstance()->Process(this, dt, gameObject);
	if (state == GUNROTATION_STATE_NORMAL && GetTickCount64() - lastShoot > GUN_RECOIL_TIME)
	{
		lastShoot = GetTickCount64();
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x + 10.0f, y - 8.0f , -0.2, 0.0f, 1));
	}
}

void CGunRotation::Render()
{
	int aniID = -1;
	if (state == GUNROTATION_STATE_HIDDEN)
		aniID = ID_ANI_GUNROTATION_HIDDEN;
	else
	{
		if (bill->GetX() < x)
		{
			if (radius >= (PI / 6) && radius < (PI / 4))
				aniID = ID_ANI_GUNROTATION_SHOT_1;
			else if (radius >= (PI / 4) && radius < (5 * PI / 12))
				aniID = ID_ANI_GUNROTATION_SHOT_0;
			else if (radius >= -(PI / 6) && radius < (PI / 6))
				aniID = ID_ANI_GUNROTATION_SHOT_2;
			else if (radius >= -(PI / 4) && radius < -(PI / 6))
				aniID = ID_ANI_GUNROTATION_SHOT_3;
			else if (radius >= -(5 * PI / 6) && radius < -(PI / 4))
				aniID = ID_ANI_GUNROTATION_SHOT_4;
		}
		else
		{
			if (radius >= (PI / 6) && radius < (PI / 4))
				aniID = ID_ANI_GUNROTATION_SHOT_10;
			else if (radius >= (PI / 4) && radius < (5 * PI / 12))
				aniID = ID_ANI_GUNROTATION_SHOT_7;
			else if (radius >= -(PI / 6) && radius < (PI / 6))
				aniID = ID_ANI_GUNROTATION_SHOT_6;
			else if (radius >= -(PI / 4) && radius < -(PI / 6))
				aniID = ID_ANI_GUNROTATION_SHOT_9;
			else if (radius >= -(5 * PI / 6) && radius < -(PI / 4))
				aniID = ID_ANI_GUNROTATION_SHOT_8;
		}
		if (aniID == -1)
		{
			if (bill->GetY() < y)
				aniID = ID_ANI_GUNROTATION_SHOT_11;
			else
				aniID = ID_ANI_GUNROTATION_SHOT_5;
		}
	}
	if (aniID == -1)
		aniID = ID_ANI_GUNROTATION_SHOT_3;
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
}

void CGunRotation::LoadAnimation()
{
	CTextures* texture = CTextures::GetInstance();
	texture->Add(TEXTURE_GUNROTATION_ID, L"./Resources/Images/wall_turret_all.png");
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;
	sprites->Add(ID_ANI_GUNROTATION_HIDDEN, 96, 64, 128, 96, texture->Get(TEXTURE_GUNROTATION_ID));

	ani = new CAnimation(100);
	ani->Add(ID_ANI_GUNROTATION_HIDDEN);

	animations->Add(ID_ANI_GUNROTATION_HIDDEN, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOW, 96, 32, 128, 64, texture->Get(TEXTURE_GUNROTATION_ID));

	ani = new CAnimation(200);
	ani->Add(ID_ANI_GUNROTATION_SHOW);
	ani->oneTimeAnimation = true;
	animations->Add(ID_ANI_GUNROTATION_SHOW, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_0, 0, 0, 32, 32, texture->Get(TEXTURE_GUNROTATION_ID));

	ani = new CAnimation(100);

	ani->Add(ID_ANI_GUNROTATION_SHOT_0);

	animations->Add(ID_ANI_GUNROTATION_SHOT_0, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_1, 0, 32, 32, 64, texture->Get(TEXTURE_GUNROTATION_ID));

	ani = new CAnimation(100);
	ani->Add(ID_ANI_GUNROTATION_SHOT_1);

	animations->Add(ID_ANI_GUNROTATION_SHOT_1, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_2, 0, 64, 32, 96, texture->Get(TEXTURE_GUNROTATION_ID));

	ani = new CAnimation(100);

	ani->Add(ID_ANI_GUNROTATION_SHOT_2);

	animations->Add(ID_ANI_GUNROTATION_SHOT_2, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_3, 0, 96, 32, 128, texture->Get(TEXTURE_GUNROTATION_ID));

	ani = new CAnimation(100);
	ani->Add(ID_ANI_GUNROTATION_SHOT_3);

	animations->Add(ID_ANI_GUNROTATION_SHOT_3, ani);


	sprites->Add(ID_ANI_GUNROTATION_SHOT_4, 0, 128, 32, 160, texture->Get(TEXTURE_GUNROTATION_ID));
	ani = new CAnimation(100);

	ani->Add(ID_ANI_GUNROTATION_SHOT_4);

	animations->Add(ID_ANI_GUNROTATION_SHOT_4, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_5, 96, 96, 128, 128, texture->Get(TEXTURE_GUNROTATION_ID));
	ani = new CAnimation(100);

	ani->Add(ID_ANI_GUNROTATION_SHOT_5);

	animations->Add(ID_ANI_GUNROTATION_SHOT_5, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_6, 96, 128, 128, 160, texture->Get(TEXTURE_GUNROTATION_ID));
	ani = new CAnimation(100);

	ani->Add(ID_ANI_GUNROTATION_SHOT_6);
	animations->Add(ID_ANI_GUNROTATION_SHOT_6, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_7, 192, 96, 224, 128, texture->Get(TEXTURE_GUNROTATION_ID));
	ani = new CAnimation(100);
	ani->Add(ID_ANI_GUNROTATION_SHOT_7);

	animations->Add(ID_ANI_GUNROTATION_SHOT_7, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_8, 194, 96, 224, 128, texture->Get(TEXTURE_GUNROTATION_ID));

	ani = new CAnimation(100);
	ani->Add(ID_ANI_GUNROTATION_SHOT_8);

	animations->Add(ID_ANI_GUNROTATION_SHOT_8, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_9, 192, 32, 224, 64, texture->Get(TEXTURE_GUNROTATION_ID));
	ani = new CAnimation(100);
	ani->Add(ID_ANI_GUNROTATION_SHOT_9);
		
	animations->Add(ID_ANI_GUNROTATION_SHOT_9, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_10, 192, 0, 224, 32, texture->Get(TEXTURE_GUNROTATION_ID));
	ani = new CAnimation(100);
	ani->Add(ID_ANI_GUNROTATION_SHOT_10);
	animations->Add(ID_ANI_GUNROTATION_SHOT_10, ani);

	sprites->Add(ID_ANI_GUNROTATION_SHOT_11, 96, 0, 128, 32, texture->Get(TEXTURE_GUNROTATION_ID));

	ani = new CAnimation(100);
	ani->Add(ID_ANI_GUNROTATION_SHOT_11);
	animations->Add(ID_ANI_GUNROTATION_SHOT_11, ani);

}

void CGunRotation::SetState(int state)
{
	switch (state)
	{
		case GUNROTATION_STATE_HIDDEN:
		{
			CAnimations::GetInstance()->Get(ID_ANI_GUNROTATION_HIDDEN)->SetStartAnimation(CAnimations::GetInstance()->Get(ID_ANI_GUNROTATION_SHOW));
			hp = 999999;
			break;
		}
		case GUNROTATION_STATE_NORMAL:
		{
			CAnimations::GetInstance()->Get(ID_ANI_GUNROTATION_SHOT_0)->SetStartAnimation(CAnimations::GetInstance()->Get(ID_ANI_GUNROTATION_SHOW));
			hp = 3;
			break;
		}
	}
	CGameObject::SetState(state);
}

void CGunRotation::OnNoCollision(DWORD dt)
{
	if (state == GUNROTATION_STATE_NORMAL)
	{
		if (GetTickCount64() - lastTurn >= GUN_ROTATION_DELAY && lastTurn != -1)
		{
			lastTurn = GetTickCount64();
			float left, top, down, right;
			bill->GetBoundingBox(left, top, down, right);
			float billWidth = right - left;
			float billHeight = down - top;
			radius = -Radius(left + billWidth / 2, top + billHeight / 2, x + 16, y + 16);
		}
	}
	if (abs(bill->GetX() - x) <= 100 && state == GUNROTATION_STATE_HIDDEN)
	{
		this->SetState(GUNROTATION_STATE_NORMAL);
		lastTurn = GetTickCount64() + 200;
	}
	if (abs(bill->GetX() - x) > 100 && state == GUNROTATION_STATE_NORMAL)
		this->SetState(GUNROTATION_STATE_HIDDEN);
}

void CGunRotation::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 10.0f;
	top = y;
	right = left + 23.0f;
	bottom = top - 32.0f;
}

void CGunRotation::GetHit(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		Deleted = 1;
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObjectToQuadTree(new CObjectExplosion(x, y));
	}
}
