#pragma once
#include "GameObject.h"
#include "AssetID.h"
#include "RifleGun.h"

#define SOLDIER_GRAVITY 0
#define SOLDIER_RUNNING_SPEED 0.05f

class CSoldier: public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG die_start;

	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	// When no collision has been detected (triggered by CCollision::Process)
	void OnNoCollision(DWORD dt);


	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(LPCOLLISIONEVENT e);

private:
	int faceDirection = -1;

public:
	CSoldier(float x, float y);
	static void LoadAnimation();
	virtual void SetState(int state);
};

