#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "AssetID.h"
class CAirCraft: public CGameObject
{
private:
	float A;
	float time;
	float omega;
	float cycle;
	float startX;
public:
	CAirCraft(float x, float y, float vx = 0.0f, float vy = 0.35f, float omega = 0.005f, float A = 50.0f) : CGameObject(x, y)
	{
		startX = x;
		this->vx = vx;
		this->vy = vy;
		this->omega = omega;
		cycle = 2 * PI / omega;
		time = 0;
		this->A = A;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject = NULL)
	{
		time += dt;
		time = (float)((int)time % (int)cycle);
		x = startX + A * cos(omega * time);
		y = y + vy;
	}
	virtual void HandleInput() {};
	static void LoadAnimation()
	{
		CTextures* textures = CTextures::GetInstance();
		textures->Add(AIRCRAFT_TEXTURE_ID, L"./Resources/Images/aircraft.png");
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

