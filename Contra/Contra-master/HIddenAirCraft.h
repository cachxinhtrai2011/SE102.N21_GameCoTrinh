#pragma once
#include "AirCraft.h"
class CHiddenAirCraft: public CAirCraft
{
private:
	float A;
	float time;
	float omega;
	float cycle;
	float startX;
public:
	CHiddenAirCraft(float x, float y, float vx = 0.1f, float vy = 0.0f, float omega = 0.005f, float A = 5.0f) :CAirCraft(x, y)
	{
		LPSPRITE sprite = CSprites::GetInstance()->Get(ID_ANI_HIDDENAIRCRAFT);
		if (sprite == NULL)
			this->LoadAnimation();
		startX = y;
		this->vx = vx;
		this->vy = vy;
		this->omega = omega;
		cycle = 2 * PI / omega;
		time = 0;
		this->A = A;
	}
	void Render()
	{
		CAnimations::GetInstance()->Get(ID_ANI_HIDDENAIRCRAFT)->Render(x, y);
	}
	static void LoadAnimation()
	{
		LPTEXTURE texture = CTextures::GetInstance()->Get(AIRCRAFT_TEXTURE_ID);
		if (texture == NULL)
		{
			CAirCraft::LoadAnimation();
			texture = CTextures::GetInstance()->Get(AIRCRAFT_TEXTURE_ID);
		}
		CSprites* sprites = CSprites::GetInstance();
		sprites->Add(ID_ANI_HIDDENAIRCRAFT, 2, 0, 27, 15, texture);
		LPANIMATION ani = new CAnimation(100);
		ani->Add(ID_ANI_HIDDENAIRCRAFT);
		CAnimations::GetInstance()->Add(ID_ANI_HIDDENAIRCRAFT, ani);
	}
	int IsCollidable() { return 1; }
	void OnNoCollision(DWORD dt)
	{
		time += dt;
		time = (float)((int)time % (int)cycle);
		x += vx  * dt;
		y +=  A * cos(omega * time);
	}
	void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
	{
		if (e->obj->IsBlocking() && e->nx != 0)
			vx = -vx;
	}
};

