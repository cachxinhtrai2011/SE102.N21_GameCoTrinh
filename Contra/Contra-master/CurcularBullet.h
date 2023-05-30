#pragma once
#include "Bullet.h"

#define RADIUS 25.0f
#define PI 3.141517f
class CCurcularBullet: public CBullet
{
private:
	float Ix;
	float Iy;
	float radius;
	float deg;
	float vdeg;
public:
	CCurcularBullet(float x, float y, float vx = 0.5f, float vy = 0.0f) : CBullet(x, y, vx, vy)
	{
		float vector_abs = sqrt(vx * vx + vy * vy);
		Ix = x + (RADIUS / vector_abs) * vx;
		Iy = y + (RADIUS / vector_abs) * vy;
		radius = RADIUS;
		float cos = -(Ix - x)/radius;
		if (Ix == x)
			cos = 0;
		deg = acos(cos);
		if (x < Ix)
			vdeg = 0.05f;
		else
			vdeg = -0.05f;
		LPANIMATION ani = CAnimations::GetInstance()->Get(ID_ANI_BULLET_F);
		if (ani == NULL)
		{
			 LoadAnimation();
			 ani = CAnimations::GetInstance()->Get(ID_ANI_BULLET_F);
		}
		bulletAnimation = ani;
	}
	void Update(DWORD dt,vector<LPGAMEOBJECT> *gameObject = NULL)
	{
		Ix = Ix + vx * dt;
		Iy = Iy + vy * dt;
		x = Ix + radius * cos(deg);
		y = Iy + radius * sin(deg);
		deg = deg + vdeg * dt;
	}
	void Render()
	{
		CBullet::Render();
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
		CSprites::GetInstance()->Add(ID_ANI_BULLET_F, 41, 37, 48, 44, texture);
		LPANIMATION ani = new CAnimation(100);
		ani->Add(ID_ANI_BULLET_F);
		CAnimations::GetInstance()->Add(ID_ANI_BULLET_F, ani);
	}
};

