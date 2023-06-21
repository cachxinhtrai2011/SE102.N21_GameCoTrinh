#pragma once
#include "Scene.h"
#include "Fonts.h"
#include "Game.h"
#include "Text.h"
class CStartScene: public CScene
{
private:
	CTexture* background;
	CSprite* cursor;
	D3DXVECTOR2 cursorPos;
	vector<CText*> texts;
public:
	CStartScene(int id, LPCWSTR filePath);
	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();
	void AddText(CText* text);
	void SetCusorPos(float x, float y) { cursorPos.x = x, cursorPos.y = y; }
	void GetCursorPos(float& x, float& y) { x = cursorPos.x; y = cursorPos.y; }
};

