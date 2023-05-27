#include "Sprite.h"
#include "Game.h"
#include "debug.h"
#include "string"
CSprite::CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex, float scaleX, float scaleY)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->scaleX = scaleX;
	this->scaleY = scaleY;

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = this->left / (float)tex->getWidth();
	sprite.TexCoord.y = this->top / (float)tex->getHeight();

	int spriteWidth = (this->right - this->left);
	int spriteHeight = (this->bottom - this->top);

	sprite.TexSize.x = spriteWidth / (float)tex->getWidth();
	sprite.TexSize.y = spriteHeight / (float)tex->getHeight();

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f,  1.0f);
	sprite.TextureIndex = 0;
	if (scaleX < 0)
	{
		sprite.TexCoord.x = sprite.TexCoord.x - (scaleX) * sprite.TexSize.x;
		sprite.TexSize.x = sprite.TexSize.x * scaleX;
	}
	if (scaleY < 0)
	{
		sprite.TexCoord.y = sprite.TexCoord.y - (scaleY)*sprite.TexSize.y;
		sprite.TexSize.y = sprite.TexSize.y * scaleY;
	}

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, -1.0f);
}

void CSprite::Draw(float x, float y ,float rotationDeg, float reSizeX, float reSizeY)
{
	CGame* g = CGame::GetInstance();
	float cx, cy;
	g->GetCamPos(cx, cy);

	cx = (FLOAT)floor(cx);
	cy = (FLOAT)floor(cy);

	x = (FLOAT)floor(x);
	y = (FLOAT)floor(y);

	//D3DXVECTOR2 pos = g->setWorldToSceen(D3DXVECTOR2(x, y));


	int spriteWidth = (this->right - this->left);
	int spriteHeight = (this->bottom - this->top);
	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, x - cx, (g->GetBackBufferHeight() - y + cy), 0.1f);
	D3DXMATRIX matRotation;
	D3DXMatrixRotationZ(&matRotation, rotationDeg);
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, reSizeX, reSizeY, 1.0f);
	this->sprite.matWorld = (this->matScaling * matScale * matRotation * matTranslation);
	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}