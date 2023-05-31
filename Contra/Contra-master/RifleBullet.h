#pragma once
#include "Bullet.h"
class CRifleBullet: public CBullet
{
public:
	CRifleBullet(float x, float y, float vx = 0.5f, float vy = 0.5f) : CBullet(x, y, vx, vy) {
		bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_RIFLE);
		if (bulletAnimation == NULL)
		{
			this->LoadAnimation();
			bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_RIFLE);
		}
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject = NULL)
	{
		CBullet::Update(dt);
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
};

