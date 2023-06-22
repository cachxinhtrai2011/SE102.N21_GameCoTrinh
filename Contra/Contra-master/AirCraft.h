#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "AssetID.h"
#include "PlayScene.h"
#include "Game.h"
#include "ObjectExplosion.h"
#include "Bill.h"
class CAirCraft: public CGameObject
{
private:
public:
	CAirCraft(float x, float y) : CGameObject(x, y){}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject = NULL)
	{
		CCollision::GetInstance()->Process(this, dt, gameObject);
	}
	static void LoadAnimation()
	{
		if (CTextures::GetInstance()->Get(AIRCRAFT_TEXTURE_ID) != NULL)
			return;
		CTextures* textures = CTextures::GetInstance();
		textures->Add(AIRCRAFT_TEXTURE_ID, L"./Resources/Images/aircraft.png");
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt) {
		x += vx * dt;
		y += vy * dt;
		vy += Bill_GRAVITY;
	}

	virtual void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
	{
		if (e->ny != 0 && e->obj->IsBlocking())
			vy = 0;
		if (dynamic_cast<CBill*>(e->obj))
		{
			Deleted = 1;
			this->PowerUp((CBill*)e->obj);
		}
	}
	virtual void PowerUp(CBill* bill) {}
};

