#include "Soldier.h"
#include "Bill.h"
#include "NormalExplosion.h"
extern CBill* bill;
#define DIETIMEOUT 300

void CSoldier::Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject)
{
	if (state == SOLDIER_STATE_DEATH)
	{
		if (GetTickCount64() - dieStart >= DIETIMEOUT)
		{
			Deleted = 1;
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObjectToQuadTree(new CNormalExplosion(x, y));
		}
		else
			OnNoCollision(dt);
	}
	else
		CCollision::GetInstance()->Process(this, dt, gameObject);
}

void CSoldier::Render()
{
	int aniID = -1;
	if (state == SOLDIER_STATE_RUNNING)
		aniID = ID_ANI_SOLDIER_RUNNING;
	else if (state == SOLDIER_STATE_SHOT)
		aniID = ID_ANI_SOLDIER_SHOT;
	else if (state == SOLDIER_STATE_LAYDOWN)
		aniID = ID_ANI_SOLDIER_LAYDOWN;
	else if (state == SOLDIER_STATE_DEATH)
		aniID = ID_ANI_SOLDIER_SHOTED;
	if (aniID == -1)
		aniID = ID_ANI_SOLDIER_RUNNING;
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
}

void CSoldier::SetState(int state) {
	if (state == SOLDIER_STATE_DEATH)
	{
		dieStart = GetTickCount64();
		vx = 0.02;
		vy = 0.25;
	}
	CGameObject::SetState(state);
}
void CSoldier::LoadAnimation()
{
	CTextures* texture = CTextures::GetInstance();
	texture->Add(TEXTURE_SOLDIER_ID, L"./Resources/Images/Soldier.png");
	CSprites* sprites = CSprites::GetInstance();
	sprites->Add(ID_ANI_SOLDIER_RUNNING + 5, 0, 0, 16, 32, texture->Get(TEXTURE_SOLDIER_ID));
	sprites->Add(ID_ANI_SOLDIER_RUNNING + 4, 18, 0, 34, 32, texture->Get(TEXTURE_SOLDIER_ID));
	sprites->Add(ID_ANI_SOLDIER_RUNNING + 3, 36, 0, 52, 32, texture->Get(TEXTURE_SOLDIER_ID));
	sprites->Add(ID_ANI_SOLDIER_RUNNING + 2, 54, 0, 70, 32, texture->Get(TEXTURE_SOLDIER_ID));
	sprites->Add(ID_ANI_SOLDIER_RUNNING + 1, 72, 0, 88, 32, texture->Get(TEXTURE_SOLDIER_ID));
	sprites->Add(ID_ANI_SOLDIER_RUNNING, 90, 0, 106, 32, texture->Get(TEXTURE_SOLDIER_ID));

	sprites->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 5, 0, 0, 16, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f);
	sprites->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 4, 18, 0, 34, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f);
	sprites->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 3, 36, 0, 52, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f);
	sprites->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 2, 54, 0, 70, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f);
	sprites->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 1, 72, 0, 88, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f );
	sprites->Add(ID_ANI_SOLDIER_RUNNING_RIGHT, 90, 0, 106, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f);

	LPANIMATION ani = new CAnimation(100);
	CAnimations* animations = CAnimations::GetInstance();
	ani->Add(ID_ANI_SOLDIER_RUNNING);
	ani->Add(ID_ANI_SOLDIER_RUNNING + 1);
	ani->Add(ID_ANI_SOLDIER_RUNNING + 2);
	ani->Add(ID_ANI_SOLDIER_RUNNING + 3);
	ani->Add(ID_ANI_SOLDIER_RUNNING + 4);
	ani->Add(ID_ANI_SOLDIER_RUNNING + 5);

	animations->Add(ID_ANI_SOLDIER_RUNNING, ani);

	ani = new CAnimation(100);

	ani->Add(ID_ANI_SOLDIER_RUNNING_RIGHT);
	ani->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 1);
	ani->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 2);
	ani->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 3);
	ani->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 4);
	ani->Add(ID_ANI_SOLDIER_RUNNING_RIGHT + 5);


	animations->Add(ID_ANI_SOLDIER_RUNNING_RIGHT, ani);
	/////////////////////////////////////////////////////

	sprites->Add(ID_ANI_SOLDIER_JUMPING, 108, 0, 124, 32, texture->Get(TEXTURE_SOLDIER_ID));
	sprites->Add(ID_ANI_SOLDIER_JUMPING_RIGHT, 108, 0, 124, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SOLDIER_JUMPING);
	animations->Add(ID_ANI_SOLDIER_JUMPING, ani);


	ani = new CAnimation(100);
	ani->Add(ID_ANI_SOLDIER_JUMPING_RIGHT);
	animations->Add(ID_ANI_SOLDIER_JUMPING_RIGHT, ani);
	//////////////////////////////////////////////////////////////////////////////////
	sprites->Add(ID_ANI_SOLDIER_SHOT, 126, 0, 150, 32, texture->Get(TEXTURE_SOLDIER_ID));
	sprites->Add(ID_ANI_SOLDIER_SHOT + 1, 152, 0, 176, 32, texture->Get(TEXTURE_SOLDIER_ID));

	sprites->Add(ID_ANI_SOLDIER_SHOT_RIGHT, 126, 0, 150, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f);
	sprites->Add(ID_ANI_SOLDIER_SHOT_RIGHT + 1, 152, 0, 176, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f);

	ani = new CAnimation(100);
	ani->Add(ID_ANI_SOLDIER_SHOT);
	ani->Add(ID_ANI_SOLDIER_SHOT + 1);

	animations->Add(ID_ANI_SOLDIER_SHOT, ani);

	ani = new CAnimation(100);

	ani->Add(ID_ANI_SOLDIER_SHOT_RIGHT);
	ani->Add(ID_ANI_SOLDIER_SHOT_RIGHT + 1);
	animations->Add(ID_ANI_SOLDIER_SHOT_RIGHT, ani);
	//////////////////////////////////////////////////////////////////////////////////
	sprites->Add(ID_ANI_SOLDIER_SHOTED, 212, 0, 227, 32, texture->Get(TEXTURE_SOLDIER_ID));
	ani = new CAnimation(100);
	ani->Add(ID_ANI_SOLDIER_SHOTED);
	animations->Add(ID_ANI_SOLDIER_SHOTED, ani);

}

void CSoldier::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y - 32;
}

void CSoldier::OnNoCollision(DWORD dt)
{
	x += -faceDirection * dt * vx;
	y += vy * dt;
	vy += Bill_GRAVITY * dt;
}

void CSoldier::OnCollisionWith(LPCOLLISIONEVENT e)
{
	vy = 0;
}

void CSoldier::GetHit(int damage)
{
	SetState(SOLDIER_STATE_DEATH);
}
