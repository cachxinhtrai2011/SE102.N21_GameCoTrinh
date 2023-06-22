#pragma once
#include "GameObject.h"
#include "BillInputHandler.h"
#include "NormalGun.h"
#include "AssetID.h"
#include "Life.h"


class CBill : public CGameObject
{
private:
	CGun* gun;
	int invincibleDuration;
	vector<CLife*>* life;
public:
	int isOnGround;
	int isBlocking;
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
		life = new vector<CLife*>();
		life->push_back(new CLife());
		life->push_back(new CLife());
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject = NULL);
	void Render();
	int IsEnemy() { return 0; }
	void SetState(int state);
	void SetFaceDirection(int faceD) { faceDirection = faceD; if (vx > 0) vx = faceDirection * vx; else vx = -faceDirection * vx; }
	void SetHandler(CBillInputHandler* inputHandler) { handler = inputHandler; }
	static void LoadAnimation();
	void SetGun(CGun* newGun) { gun = newGun; }
	void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt = 0);
	void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	int IsOnGround() { return isOnGround; }
	void setIsOnGround(int value) { isOnGround = value; }
	void setIsBlocking(int value) { isBlocking = value; }
	void GetHit(int damage) { SetState(BILL_STATE_DEAD); }
};