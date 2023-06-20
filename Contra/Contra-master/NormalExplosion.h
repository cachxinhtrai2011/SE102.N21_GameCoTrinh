#pragma once
#include "Explosion.h"
#define DEFAULT_LIVE_TIME 100
class CNormalExplosion: public CExplosion
{
public:
	CNormalExplosion(float x, float y): CExplosion(x, y, DEFAULT_LIVE_TIME * 3) {}
	static void LoadAniamtion() {
		CExplosion::LoadAnimation();
		CTextures* textures = CTextures::GetInstance();
		CSprites* sprites = CSprites::GetInstance();
		CAnimations* animations = CAnimations::GetInstance();
		sprites->Add(ID_ANI_NORMAL_EXPLOSION, 0, 0, 25, 32, textures->Get(TEXTURE_EXPLOSION_ID));
		sprites->Add(ID_ANI_NORMAL_EXPLOSION + 1, 26, 0, 55, 32, textures->Get(TEXTURE_EXPLOSION_ID));
		sprites->Add(ID_ANI_NORMAL_EXPLOSION + 2, 56, 0, 89, 32, textures->Get(TEXTURE_EXPLOSION_ID));

		CAnimation* ani = new CAnimation(DEFAULT_LIVE_TIME);
		ani->Add(ID_ANI_NORMAL_EXPLOSION);
		ani->Add(ID_ANI_NORMAL_EXPLOSION + 1);
		ani->Add(ID_ANI_NORMAL_EXPLOSION + 2);
		
		animations->Add(ID_ANI_NORMAL_EXPLOSION, ani);
	}
	void Render()
	{
		if (GetTickCount64() - startTime < liveTime)
			CAnimations::GetInstance()->Get(ID_ANI_NORMAL_EXPLOSION)->Render(x, y);
		else
			this->Deleted = 1;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = x, top = y; right = 25, bottom = 32; }

};

