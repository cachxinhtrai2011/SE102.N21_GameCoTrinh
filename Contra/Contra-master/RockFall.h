#pragma once
#include "GameObject.h"
#include "AssetID.h"
#define FALL_SPEED 0.25f
class CRockFall: public CGameObject
{
private:
	int shakeTime = 100;
public:
	CRockFall(float x, float y) :CGameObject(x, y) { state = ROCKFALL_STATE_IDLE; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject);
	void Render();
	static void LoadAnimation();
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; }
	void SetState(int state);
};

