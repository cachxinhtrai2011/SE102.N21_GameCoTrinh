#include "StartScene.h"
#include "AssetID.h"
#include "GameInputHandler.h";
#include <iostream>
#include <fstream>

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_BACKGROUND	1
#define SCENE_SECTION_TEXT	2
#define MAX_SCENE_LINE 1024
CStartScene::CStartScene(int id, LPCWSTR filePath):CScene(id, filePath)
{
	background = NULL;
	cursor = NULL;
	key_handler = new CGameInputHandler(this);
}
void CStartScene::Load()
{
	
	background = CGame::GetInstance()->LoadTexture(L".\\Resources\\Images\\intro1.png");
	LPTEXTURE cursor_tex = CGame::GetInstance()->LoadTexture(L".\\Resources\\Images\\yellowfalcon.png");
	cursor = new CSprite(1712, 0, 0, cursor_tex->getWidth(), cursor_tex->getHeight(), cursor_tex);
	cursorPos.x = 10.0f;
	cursorPos.y = 110.0f;
}

void CStartScene::Unload()
{
}

void CStartScene::Update(DWORD dt)
{
}

void CStartScene::Render()
{
	CGame::GetInstance()->Draw(113.0f, 113.0f, background);
	cursor->Draw(cursorPos.x, cursorPos.y);
}

void CStartScene::AddText(CText* text)
{
	texts.push_back(text);
}
