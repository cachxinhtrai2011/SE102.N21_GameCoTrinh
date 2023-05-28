#pragma once
#include "Bullet.h"
class CBillBullet : public CBullet
{
public:
	CBillBullet(float x, float y, float vx = 0.5f, float vy = 0.5f): CBullet(x,y,vx,vy) {
		bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_NORMAL);
		if (bulletAnimation == NULL)
		{
			this->LoadAnimation();
			bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_NORMAL);
		}
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject = NULL);
	static void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithSoldier(LPCOLLISIONEVENT e);
};

