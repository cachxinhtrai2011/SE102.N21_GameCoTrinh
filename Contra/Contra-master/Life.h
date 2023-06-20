#pragma once
#include "AssetID.h"
#include "GameObject.h"
class CLife
{
public:

	static void LoadAnimation() {
		CTextures* tex = CTextures::GetInstance();
		tex->Add(TEXTURE_LIFE_ID, TEXTURE_LIFE_PATH);
		CSprites::GetInstance()->Add(ID_LIFE_SPRITE,12, 0, 21, 16, tex->Get(TEXTURE_LIFE_ID));
	}

	void Render(float x, float y)
	{
		if (CSprites::GetInstance()->Get(ID_LIFE_SPRITE) == NULL)
			LoadAnimation();
		CSprites::GetInstance()->Get(ID_LIFE_SPRITE)->Draw(x, y);
	}
};

