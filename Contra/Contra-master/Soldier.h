#pragma once
#include "GameObject.h"
#include "AssetID.h"
#include "RifleGun.h"
class CSoldier: public CGameObject
{
private:
	int faceDirection = -1;
public:
	CSoldier(float x, float y) : CGameObject(x, y) { state = SOLDIER_STATE_RUNNING; vx = -0.03; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject);
	void Render();
	static void LoadAnimation();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	// When no collision has been detected (triggered by CCollision::Process)
	void OnNoCollision(DWORD dt);

	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetHit(int damage);
};

