#include "Soldier.h"

CSOLDIER::CSOLDIER(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	//this->ay = SOLDIER_GRAVITY;
	die_start = -1;
	SetState(SOLDIER_STATE_RUNNING_RIGHT);
}

void CSOLDIER::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SOLDIER_STATE_JUMP)
	{
		left = x - SOLDIER_BBOX_WIDTH / 2;
		top = y - SOLDIER_BBOX_HEIGHT_DIE / 2;
		right = left + SOLDIER_BBOX_WIDTH;
		bottom = top + SOLDIER_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - SOLDIER_BBOX_WIDTH / 2;
		top = y - SOLDIER_BBOX_HEIGHT / 2;
		right = left + SOLDIER_BBOX_WIDTH;
		bottom = top + SOLDIER_BBOX_HEIGHT;
	}
}

void CSOLDIER::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CSOLDIER::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CSOLDIER*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CSOLDIER::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == SOLDIER_STATE_JUMP) && (GetTickCount64() - die_start > SOLDIER_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CSOLDIER::Render()
{
	int aniId = ID_ANI_SOLDIER_RUNNING_RIGHT;
	if (state == SOLDIER_STATE_JUMP)
	{
		aniId = ID_ANI_SOLDIER_JUMP;
	}
	else if (state == SOLDIER_STATE_FIRE_RIGHT)
	{
		aniId = ID_ANI_SOLDIER_FIRE_RIGHT;
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CSOLDIER::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOLDIER_STATE_JUMP:
		die_start = GetTickCount64();
		y += (SOLDIER_BBOX_HEIGHT - SOLDIER_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case SOLDIER_STATE_RUNNING_RIGHT:
		break;

	}
}
