#pragma once
#include "GameObject.h"

#define SNIPER_GRAVITY 0.002f
#define SNIPER_WALKING_SPEED 0.05f


#define SNIPER_BBOX_WIDTH 16
#define SNIPER_BBOX_HEIGHT 14
#define SNIPER_BBOX_HEIGHT_DIE 7

#define SNIPER_DIE_TIMEOUT 500

#define SNIPER_STATE_SHOOTING_DOWN_RIGHT 100
#define SNIPER_STATE_SHOOTING_UP_RIGHT 200
#define SNIPER_STATE_SNIPER_SHOOTING_STRAIGHT_RIGHT 300
#define SNIPER_STATE_SNIPER_DEAD 400

#define ID_ANI_SNIPER_SHOOTING_DOWN_RIGHT 1201
#define ID_ANI_SNIPER_SHOOTING_UP_RIGHT 1202
#define ID_ANI_SNIPER_SHOOTING_STRAIGHT_RIGHT 1203
#define ID_ANI_SNIPER_DEAD 1204

class CSNIPER : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CSNIPER(float x, float y);
	virtual void SetState(int state);
};