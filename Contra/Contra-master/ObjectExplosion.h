#pragma once
#include "Explosion.h"
#define DEFAULT_LIVE_TIME 100
class CObjectExplosion: public CExplosion
{
public:
	CObjectExplosion(float x, float y) : CExplosion(x, y, DEFAULT_LIVE_TIME * 3) {}
	static void LoadAniamtion() {
		CExplosion::LoadAnimation();
		CTextures* textures = CTextures::GetInstance();
		CSprites* sprites = CSprites::GetInstance();
		CAnimations* animations = CAnimations::GetInstance();
		sprites->Add(ID_ANI_OBJECT_EXPLOSION, 90, 0, 106, 32, textures->Get(TEXTURE_EXPLOSION_ID));
		sprites->Add(ID_ANI_OBJECT_EXPLOSION + 1, 107, 0, 131, 32, textures->Get(TEXTURE_EXPLOSION_ID));
		sprites->Add(ID_ANI_OBJECT_EXPLOSION + 2, 132, 0, 163, 32, textures->Get(TEXTURE_EXPLOSION_ID));

		CAnimation* ani = new CAnimation(DEFAULT_LIVE_TIME);
		ani->Add(ID_ANI_OBJECT_EXPLOSION);
		ani->Add(ID_ANI_OBJECT_EXPLOSION + 1);
		ani->Add(ID_ANI_OBJECT_EXPLOSION + 2);

		animations->Add(ID_ANI_OBJECT_EXPLOSION, ani);
	}
	void Render()
	{
		if (GetTickCount64() - startTime < liveTime)
			CAnimations::GetInstance()->Get(ID_ANI_OBJECT_EXPLOSION)->Render(x, y);
		else
			this->Deleted = 1;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = x, top = y; right = 31, bottom = 32; }
};

