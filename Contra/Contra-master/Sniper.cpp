#include "Sniper.h"
#include "Bill.h"
#include "RifleBullet.h"

#define RECOIL_TIME 3000

extern CBill* bill;
void CSniper::Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject)
{
	if (bill->GetX() < x)
		faceDirection = -1;
	else
		faceDirection = 1;
	if (state == SNIPER_STATE_SHOT && GetTickCount64() -lastShot >= RECOIL_TIME )
	{
		lastShot = GetTickCount64();
		if (bill->GetY() - y >= -100)
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x, y, faceDirection * 0.35f, 0.01f, 1));
		else if (bill->GetY() - y <= 100)
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x, y, faceDirection * 0.35, -0.35f, 1));
		else
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x, y, faceDirection * 0.35, 0.0f, 1));
	}
	if (abs(bill->GetX() - x) <= 100)
		SetState(SNIPER_STATE_SHOT);
	else if(state != SNIPER_STATE_NORMAl)
		SetState(SNIPER_STATE_NORMAl);
}

void CSniper::Render()
{
	int aniID = -1;
	if (faceDirection == -1)
	{
		if (state == SNIPER_STATE_NORMAl)
			aniID = ID_ANI_SNIPER_NORMAL;
		else if (state = SNIPER_STATE_SHOT)
			if (bill->GetY() - y >= -100)
				aniID = ID_ANI_SNIPER_SHOT_UP;
			else if (bill->GetY() - y <= 100)
				aniID = ID_ANI_SNIPER_SHOT_DOWN;
			else aniID = ID_ANI_SNIPER_SHOT;
	}
	else
	{

		if (state == SNIPER_STATE_NORMAl)
			aniID = ID_ANI_SNIPER_NORMAL_RIGHT;
		else if (state = SNIPER_STATE_SHOT)
			if (bill->GetY() - y >= -100)
				aniID = ID_ANI_SNIPER_SHOT_UP_RIGHT;
			else if (bill->GetY() - y <= 100)
				aniID = ID_ANI_SNIPER_SHOT_DOWN_RIGHT;
			else aniID = ID_ANI_SNIPER_SHOT_RIGHT;
	}
	if(aniID  == -1)
		aniID = ID_ANI_SNIPER_NORMAL;
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
}

void CSniper::LoadAnimation()
{
	CTextures* texture = CTextures::GetInstance();
	texture->Add(TEXTURE_SNIPER_ID, L"./Resources/Images/rifleman.png");
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	sprites->Add(ID_ANI_SNIPER_NORMAL, 0, 0, 23, 38,texture->Get(TEXTURE_SNIPER_ID));
	sprites->Add(ID_ANI_SNIPER_NORMAL_RIGHT, 0, 0, 23, 38, texture->Get(TEXTURE_SNIPER_ID), -1.0f);

	LPANIMATION ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_NORMAL);
	animations->Add(ID_ANI_SNIPER_NORMAL, ani);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_NORMAL);
	animations->Add(ID_ANI_SNIPER_NORMAL_RIGHT, ani);
	////////////////////////////////////////////////////////////////////////////////
	sprites->Add(ID_ANI_SNIPER_SHOT, 26, 0, 49, 38, texture->Get(TEXTURE_SNIPER_ID));
	sprites->Add(ID_ANI_SNIPER_SHOT_RIGHT, 26, 0, 49, 38, texture->Get(TEXTURE_SNIPER_ID), -1.0f);


	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_NORMAL);
	ani->Add(ID_ANI_SNIPER_SHOT);
	animations->Add(ID_ANI_SNIPER_SHOT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_NORMAL_RIGHT);
	ani->Add(ID_ANI_SNIPER_SHOT_RIGHT);
	animations->Add(ID_ANI_SNIPER_SHOT_RIGHT, ani);
	/////////////////////////////////////////////////////////////////////////////////////
	sprites->Add(ID_ANI_SNIPER_SHOT_UP, 72, 0, 89, 38, texture->Get(TEXTURE_SNIPER_ID));
	sprites->Add(ID_ANI_SNIPER_SHOT_UP_RIGHT, 72, 0, 89, 38, texture->Get(TEXTURE_SNIPER_ID), -1.0f);
	
	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_SHOT_UP);
	animations->Add(ID_ANI_SNIPER_SHOT_UP, ani);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_SHOT_UP_RIGHT);
	animations->Add(ID_ANI_SNIPER_SHOT_UP_RIGHT, ani);
	//////////////////////////////////////////////////////////////////////////////////////
	sprites->Add(ID_ANI_SNIPER_SHOT_DOWN, 92, 0, 115, 38, texture->Get(TEXTURE_SNIPER_ID));
	sprites->Add(ID_ANI_SNIPER_SHOT_DOWN_RIGHT, 92, 0, 115, 38, texture->Get(TEXTURE_SNIPER_ID), -1.0f);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_SHOT_DOWN);
	animations->Add(ID_ANI_SNIPER_SHOT_DOWN, ani);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_SHOT_DOWN_RIGHT);
	animations->Add(ID_ANI_SNIPER_SHOT_DOWN_RIGHT, ani);
	/////////////////////////////////////////////////////////////////////////////////////
	sprites->Add(ID_ANI_SNIPER_SHOW, 128, 0, 150, 38, texture->Get(TEXTURE_SNIPER_ID));
	sprites->Add(ID_ANI_SNIPER_SHOW_RIGHT, 128, 0, 150, 38, texture->Get(TEXTURE_SNIPER_ID), -1.0f);
	ani = new CAnimation(50);
	ani->Add(ID_ANI_SNIPER_SHOW);
	ani->oneTimeAnimation = true;
	animations->Add(ID_ANI_SNIPER_SHOW, ani);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_SHOW_RIGHT);
	ani->oneTimeAnimation = true;

	animations->Add(ID_ANI_SNIPER_SHOW_RIGHT, ani);
	////////////////////////////////////////////////////////////////////////////////////
	sprites->Add(ID_ANI_SNIPER_HIDDEN, 118, 0, 125, 38, texture->Get(TEXTURE_SNIPER_ID));
	sprites->Add(ID_ANI_SNIPER_HIDDEN_RIGHT, 118, 0, 125, 38, texture->Get(TEXTURE_SNIPER_ID), -1.0f);
	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_HIDDEN);
	animations->Add(ID_ANI_SNIPER_HIDDEN, ani);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_HIDDEN_RIGHT);
	animations->Add(ID_ANI_SNIPER_HIDDEN_RIGHT, ani);
	///////////////////////////////////////////////////////////////////////////////////////
	sprites->Add(ID_ANI_SNIPER_HIDDEN_SHOT, 153, 0, 176, 38, texture->Get(TEXTURE_SNIPER_ID));
	sprites->Add(ID_ANI_SNIPER_HIDDEN_SHOT_RIGHT, 153, 0, 176, 38, texture->Get(TEXTURE_SNIPER_ID), -1.0f);
	
	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_HIDDEN_SHOT);
	animations->Add(ID_ANI_SNIPER_HIDDEN_SHOT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SNIPER_HIDDEN_SHOT_RIGHT);
	animations->Add(ID_ANI_SNIPER_HIDDEN_SHOT_RIGHT, ani);
}

void CSniper::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 23;
	bottom = y + 38;
}

void CSniper::OnNoCollision(DWORD dt)
{
}

void CSniper::OnCollisionWith(LPCOLLISIONEVENT e)
{
}
