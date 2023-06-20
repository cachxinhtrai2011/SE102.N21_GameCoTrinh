#pragma once
#include "Bullet.h"
class CRifleBullet: public CBullet
{
public:
	CRifleBullet(float x, float y, float vx = 0.5f, float vy = 0.5f, int enemy = 0) : CBullet(x, y, vx, vy, enemy) {
		bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_RIFLE);
		if (bulletAnimation == NULL)
		{
			this->LoadAnimation();
			bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_RIFLE);
		}
	}
	void OnNoCollision(DWORD dt)
	{
		x += vx * dt;
		y += vy * dt;
	}
	static void LoadAnimation()
	{
		LPTEXTURE texture = CTextures::GetInstance()->Get(ID_BULLET_TEXTURE);
		if (texture == NULL)
		{
			CBullet::LoadAnimation();
			texture = CTextures::GetInstance()->Get(ID_BULLET_TEXTURE);
		}
		CSprites* sprites = CSprites::GetInstance();
		sprites->Add(ID_ANI_BULLET_RIFLE, 52, 42, 54, 44, texture);
		LPANIMATION ani = new  CAnimation(100);
		ani->Add(ID_ANI_BULLET_RIFLE);
		CAnimations::GetInstance()->Add(ID_ANI_BULLET_RIFLE, ani);
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		top = y;
		right = x + 2; 
		bottom = y - 2;
	}
	int GetDamage() { return 2; }
};
