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
	static void LoadAnimation()
	{
		LPTEXTURE texture = CTextures::GetInstance()->Get(ID_BULLET_TEXTURE);
		if (texture == NULL)
		{
			CBullet::LoadAnimation();
			texture = CTextures::GetInstance()->Get(ID_BULLET_TEXTURE);
		}
		CSprites* sprites = CSprites::GetInstance();
		sprites->Add(ID_ANI_BULLET_NORMAL, 69, 28, 73, 32, texture);
		LPANIMATION ani = new  CAnimation(100);
		ani->Add(ID_ANI_BULLET_NORMAL);
		CAnimations::GetInstance()->Add(ID_ANI_BULLET_NORMAL, ani);
	}
	void OnNoCollision(DWORD dt)
	{
		x += vx * dt;
		y += vy * dt;
		CGame* game = CGame::GetInstance();
		float camX, camY;
		CGame::GetInstance()->GetCamPos(camX, camY);
		float camWidth, camHeight;
		camWidth = CGame::GetInstance()->GetScreenWidth();
		camHeight = CGame::GetInstance()->GetScreenHeight();
		if (x < camX || x > camX + camWidth + 50 || y < camY - camHeight || y > camY + 50)
			Deleted = 1;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		top = y;
		right = x + 4;
		bottom = y - 4;
	}

	int GetDamage() { return 1; }
};

