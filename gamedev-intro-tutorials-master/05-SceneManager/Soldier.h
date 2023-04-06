#pragma once
#include "GameObject.h"

#define SOLDIER_GRAVITY 0.002f
#define SOLDIER_WALKING_SPEED 0.05f


#define SOLDIER_BBOX_WIDTH 22
#define SOLDIER_BBOX_HEIGHT 28
#define SOLDIER_BBOX_HEIGHT_DIE 7

#define SOLDIER_DIE_TIMEOUT 500

#define SOLDIER_STATE_RUNNING_RIGHT 100
#define SOLDIER_STATE_FIRE_RIGHT 200
#define SOLDIER_STATE_LAY_DOWN 300
#define SOLDIER_STATE_JUMP 400

#define ID_ANI_SOLDIER_RUNNING_RIGHT 1101
#define ID_ANI_SOLDIER_FIRE_RIGHT 1102
#define ID_ANI_SOLDIER_LAY_DOWN 1103
#define ID_ANI_SOLDIER_JUMP 1104

class CSOLDIER : public CGameObject
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
	CSOLDIER(float x, float y);
	virtual void SetState(int state);
};