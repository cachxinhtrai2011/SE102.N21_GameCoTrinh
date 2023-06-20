#pragma once
#include "Scene.h"
#include "Fonts.h"
#include "Game.h"
class CGameOverScene: public CScene 
{
private:
	CTexture* background;
	CSprite* cursor;
	D3DXVECTOR2 cursorPos;
public:
	CGameOverScene(int id, LPCWSTR filePath);
	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();
	void SetCusorPos(float x, float y) { cursorPos.x = x, cursorPos.y = y; }
	void GetCursorPos(float& x, float& y) { x = cursorPos.x; y = cursorPos.y; }
};

