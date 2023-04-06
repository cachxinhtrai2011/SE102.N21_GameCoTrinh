#include "Sniper.h"

CSNIPER::CSNIPER(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	die_start = -1;
	SetState(SNIPER_STATE_SHOOTING_DOWN_RIGHT);
}

void CSNIPER::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ID_ANI_SNIPER_DEAD)
	{
		left = x - SNIPER_BBOX_WIDTH / 2;
		top = y - SNIPER_BBOX_HEIGHT_DIE / 2;
		right = left + SNIPER_BBOX_WIDTH;
		bottom = top + SNIPER_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - SNIPER_BBOX_WIDTH / 2;
		top = y - SNIPER_BBOX_HEIGHT / 2;
		right = left + SNIPER_BBOX_WIDTH;
		bottom = top + SNIPER_BBOX_HEIGHT;
	}
}

void CSNIPER::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CSNIPER::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CSNIPER*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CSNIPER::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == ID_ANI_SNIPER_DEAD) && (GetTickCount64() - die_start > SNIPER_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CSNIPER::Render()
{
	int aniId = ID_ANI_SNIPER_SHOOTING_DOWN_RIGHT;
	if (state == ID_ANI_SNIPER_DEAD)
	{
		aniId = ID_ANI_SNIPER_DEAD;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CSNIPER::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ID_ANI_SNIPER_DEAD:
		die_start = GetTickCount64();
		y += (SNIPER_BBOX_HEIGHT - SNIPER_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case SNIPER_STATE_SHOOTING_DOWN_RIGHT:
		break;
	}
}
