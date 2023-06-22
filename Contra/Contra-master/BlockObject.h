#pragma once
#include "GameObject.h"
#include "AssetID.h"
class CBlockObject: public CGameObject
{
private:
	int tile_length;
	int isBlock;
public:
	CBlockObject(float x, float y, int tileLength = 1) :CGameObject(x, y) { tile_length = tileLength; isBlock = 1; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = x, top = y; right = x + 16 * tile_length, bottom = y - 0.5f; }
	int IsCollidable() { return 1; };
	virtual int IsBlocking() { return isBlock; };
	void setIsBlocking(int value) { isBlock = value; };
	void Render() {} //CAnimations::GetInstance()->Get(ID_GRASS)->Render(x, y); }
};

