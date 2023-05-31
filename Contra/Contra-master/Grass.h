#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "AssetID.h"
class CGrass: public CGameObject
{
public:
	CGrass(float x, float y) :CGameObject(x, y) {};
	void Render()
	{
		CAnimations::GetInstance()->Get(ID_GRASS)->Render(x,y);
	}
	int IsBlocking() { return 1; }
	static void LoadAnimation() 
	{
		CTextures* texture = CTextures::GetInstance();
		texture->Add(TEXTURE_GRASS_ID, L"./Resources/Images/grass.png");
		CSprites::GetInstance()->Add(ID_GRASS, 0, 0, 31, 15, texture->Get(TEXTURE_GRASS_ID));
		LPANIMATION ani = new CAnimation(100);
		ani->Add(ID_GRASS);
		CAnimations::GetInstance()->Add(ID_GRASS, ani);

	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		bottom = y - 20;
		right = x + 31;
		top = y;
	}
};

