#pragma once
#include "GameObject.h"
#include "BillInputHandler.h"
#include "NormalGun.h"
#include "AssetID.h"


class CBill : public CGameObject
{
private:
	CGun* gun;
public:
	BOOLEAN isSitting;
	BOOLEAN isShotting;
	int shotDirection;
	int faceDirection;
	CBillInputHandler* handler;
	CBill(float x, float y): CGameObject(x,y)
	{
		isSitting = false;
		isShotting = false;
		shotDirection = 0;
		faceDirection = 1;
		state = BILL_STATE_IDLE;
		this->handler = new CBillInputHandler();
		gun = new CNormalGun();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject = NULL);
	void Render();
	void SetState(int state);
	void SetFaceDirection(int faceD) { faceDirection = faceD; if (vx > 0) vx = faceDirection * vx; else vx = -faceDirection * vx; }
	void SetHandler(CBillInputHandler* inputHandler) { handler = inputHandler; }
	static void LoadAnimation();
	//void SetGun(CGun* newGun) { gun = newGun; }
	void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt = 0);
	void OnCollisionWithSoldier(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; }
};