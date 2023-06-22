#pragma once
#include "GameObject.h";
#include "AssetID.h";
#include "RifleGun.h"
class CSniper: public CGameObject
{
protected:
	int faceDirection = -1;
	long lastShot;

public:
	CSniper(float x, float y) : CGameObject(x, y) { state = SNIPER_STATE_NORMAl; lastShot = -1; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject);
	void Render();
	void SetState(int state) {
		if (state == SNIPER_STATE_DIE)
		{
			dieStart = GetTickCount64();
			vx = 0.02;
			vy = 0.25;
		}
		CGameObject::SetState(state);
	}
	static void LoadAnimation();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	// When no collision has been detected (triggered by CCollision::Process)
	void OnNoCollision(DWORD dt);
	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetHit(int damage);
};

