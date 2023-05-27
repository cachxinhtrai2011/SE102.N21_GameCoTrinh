#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

/*
	Clear all loaded sprites
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex, float scaleX, float scaleY)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex, scaleX, scaleY);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}