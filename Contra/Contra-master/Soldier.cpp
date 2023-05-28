#include "Soldier.h"
#include "Bill.h"

extern CBill* bill;

CSoldier::CSoldier(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = SOLDIER_GRAVITY;
	vx = 0;
	die_start = -1;
	state = SOLDIER_STATE_RUNNING;
}

void CSoldier::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOLDIER_STATE_RUNNING:
		vx = 0;
		vy = 0;
		break;
	case SOLDIER_STATE_DEATH:
		vx = 0;
		vy = 0;
		break;
	}
}


void CSoldier::Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject)
{
	if (bill->GetX() < x)
		faceDirection = -1;
	else
		faceDirection = 1;

	CGameObject::Update(dt, gameObject);
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
		aniID = ID_ANI_SOLDIER_DEATH;
	if (aniID == -1)
		aniID = ID_ANI_SOLDIER_RUNNING;
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
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

	sprites->Add(ID_ANI_SOLDIER_DEATH, 212, 0, 227, 32, texture->Get(TEXTURE_SOLDIER_ID), -1.0f);
	ani = new CAnimation(100);
	ani->Add(ID_ANI_SOLDIER_DEATH);
	animations->Add(ID_ANI_SOLDIER_DEATH, ani);

}

void CSoldier::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y - 24;
}

void CSoldier::OnNoCollision(DWORD dt)
{
	x += -faceDirection * dt * vx;
	y += vy * dt;
	vy += Bill_GRAVITY * dt;
	if (y > GROUND_Y)
	{
		vy = 0;
		y = GROUND_Y;
	}
}

void CSoldier::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CSoldier*>(e->obj)) return;

	if (e->nx != 0 )
	{
		SetState(SOLDIER_STATE_DEATH);
	}
}
