#pragma once
#include "AirCraft.h"
#include "FireGun.h"
class CLAirCraft: public CAirCraft
{
public:
	CLAirCraft(float x, float y) :CAirCraft(x, y)
	{
		LPSPRITE sprite = CSprites::GetInstance()->Get(ID_ANI_LARICRAFT);
		if (sprite == NULL)
			this->LoadAnimation();
	}
	void Render()
	{
		CAnimations::GetInstance()->Get(ID_ANI_LARICRAFT)->Render(x, y);
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
		sprites->Add(ID_ANI_LARICRAFT, 80, 0, 105, 15, texture);
		LPANIMATION ani = new CAnimation(100);
		ani->Add(ID_ANI_LARICRAFT);
		CAnimations::GetInstance()->Add(ID_ANI_LARICRAFT, ani);
	}
	void PowerUp(CBill* bill)
	{
		bill->SetGun(new CFireGun());
	}
};

