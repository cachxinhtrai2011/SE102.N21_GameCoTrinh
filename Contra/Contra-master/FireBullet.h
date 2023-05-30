#pragma once
#include "Bullet.h"
class CFireBullet:public  CBullet
{
private: 
	float rotation;
public:
	static CFireBullet* __instance;
	CFireBullet(float x, float y, float vx = 0.5f, float vy = 0.5f) :CBullet(x, y, vx, vy) 
	{
		rotation = -atan(vy / vx);
		bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_L);
		if (bulletAnimation == NULL)
		{
			this->LoadAnimation();
			bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_L);
		}
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject = NULL)
	{
		CBullet::Update(dt, gameObject);
		if (dt > 0)
			dt = -(float)(dt / 2);
		else
			dt = -(float)(dt * 2);
	}
	void Render()
	{
		if (bulletAnimation != NULL)
		{
			bulletAnimation->Render(x, y, rotation);
			bulletAnimation->Render(x + vx * 10, y + vy * 10, rotation);
			bulletAnimation->Render(x + vx * 30, y + vy * 30, rotation);
		}
	}

	static void LoadAnimation()
	{
		CTextures* tex = CTextures::GetInstance();
		LPTEXTURE texture = tex->Get(ID_BULLET_TEXTURE);
		if (texture == NULL)
		{
			CBullet::LoadAnimation();
			texture = tex->Get(ID_BULLET_TEXTURE);
		}
		CSprites::GetInstance()->Add(ID_ANI_BULLET_L, 23, 39, 38, 44, texture);
		LPANIMATION ani = new CAnimation(100);
		ani->Add(ID_ANI_BULLET_L);
		CAnimations::GetInstance()->Add(ID_ANI_BULLET_L, ani);
	}
	static CFireBullet* GetInstance(float x, float y, float vx = 0.5f, float vy =  0.5f)
	{
		if (__instance == NULL)
		{
			__instance = new CFireBullet(x, y, vx, vy);
			CGame::GetInstance()->gameObjects.push_back(__instance);
		}
		else
		{
			__instance->x = x;
			__instance->y = y;
			__instance->vx = vx;
			__instance->vy = vy;
			__instance->rotation = -atan(vy / vx);
		}
		return __instance;
	}
};

