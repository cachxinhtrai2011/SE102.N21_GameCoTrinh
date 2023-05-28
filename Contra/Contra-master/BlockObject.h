#pragma once
#include "GameObject.h"
class CBlockObject: public CGameObject
{
private:
	int tile_length;
public:
	CBlockObject(float x, float y, int tileLength = 1) :CGameObject(x, y) { tile_length = tileLength; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = x, top = y - 8; right = x + 16 * tile_length, bottom = y - 16; }
	int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; };
	void Render() {}
};

