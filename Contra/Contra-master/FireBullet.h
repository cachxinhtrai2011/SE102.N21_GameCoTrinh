#pragma once
#include "Bullet.h"
class CFireBullet:public  CBullet
{
private: 
	float rotation;
public:
	static CFireBullet* __instance;
	CFireBullet(float x, float y, float vx = 0.5f, float vy = 0.5f, int enemy = 0):CBullet(x, y, vx, vy, enemy) 
	{
		rotation = atan(vy / vx);
		bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_L);
		if (bulletAnimation == NULL)
		{
			this->LoadAnimation();
			bulletAnimation = CAnimations::GetInstance()->Get(ID_ANI_BULLET_L);
		}
	};
	void OnNoCollision(DWORD dt)
	{
		x += vx * dt;
		y += vy * dt;
	}
	void Render()
	{
		if (bulletAnimation != NULL)
		{
			bulletAnimation->Render(x, y, rotation);
			bulletAnimation->Render(x + vx * 10, y + vy * 10, rotation);
			bulletAnimation->Render(x + vx * 20, y + vy * 20, rotation);
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
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(__instance);
			
		}
		else
		{
			vector<CBullet*>* ammo = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo();
			vector<CBullet*>::iterator i = std::find(ammo->begin(), ammo->end(), __instance);
			if (i == ammo->end())
			{
				__instance = new CFireBullet(x, y, vx, vy);
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(__instance);
			}
			else
			{
				__instance->x = x;
				__instance->y = y;
				__instance->vx = vx;
				__instance->vy = vy;
				__instance->rotation = atan(vy / vx);
			}
		}
		return __instance;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		top = y;
		right = x + 30;
		bottom = y - 5;
	}
};

