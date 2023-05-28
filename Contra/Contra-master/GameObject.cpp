#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	state = -1;
}

void CGameObject::DeleteFromGameObjects()
{
	CGame* game = CGame::GetInstance();
	vector<LPGAMEOBJECT> gameObjects = CGame::GetInstance()->gameObjects;
	vector<LPGAMEOBJECT>::iterator i = std::find(gameObjects.begin(), gameObjects.end(), this);
	gameObjects.erase(i);
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	CGame* g = CGame::GetInstance();
	CGame::GetInstance()->DrawBBox(x - cx, -g->GetBackBufferHeight() * 2 + y - cy, bbox, &rect, BBOX_ALPHA + 0.25,0,0);
}

CGameObject::~CGameObject()
{
}
