#pragma once

#include "Texture.h"

class CGame;
class CSprite
{
	int id;				// Sprite ID in the sprite database
	int left;
	int top;
	int right;
	int bottom;
	float scaleX;
	float scaleY;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex, float scaleX = 1.0f, float scaleY = 1.0f);

	void Draw(float x, float y, float rotationDeg = 0.0f, float reSizeX = 1.0f, float reSizeY = 1.0f);
};

typedef CSprite* LPSPRITE;