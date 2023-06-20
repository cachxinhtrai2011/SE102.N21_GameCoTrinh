#pragma once
#include "GameObject.h"
#include "AssetID.h"
class CExplosion: public CGameObject
{
protected:
	int startTime;
	int liveTime;
public:
	static void LoadAnimation() {
		CTexture* texture = CTextures::GetInstance()->Get(TEXTURE_EXPLOSION_ID);
		if (texture == NULL)
			CTextures::GetInstance()->Add(TEXTURE_EXPLOSION_ID, TEXTURE_EXPLOSION_PATH);
	}
	CExplosion(float x, float y, int liveTime) : CGameObject(x, y) { this->liveTime = liveTime; this->startTime = GetTickCount64(); }
	virtual void Render() = 0;
};

