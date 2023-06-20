#include "GameOverScene.h"
#include "GameOverInputHandler.h"
CGameOverScene::CGameOverScene(int id, LPCWSTR filePath):CScene(id, filePath)
{
	background = NULL;
	cursor = NULL;
	key_handler = new CGameOverInputHandler(this);
}
void CGameOverScene::Load()
{
	background = CGame::GetInstance()->LoadTexture(L".\\Resources\\Images\\GameOver.png");
	LPTEXTURE cursor_tex = CGame::GetInstance()->LoadTexture(L".\\Resources\\Images\\yellowfalcon.png");
	cursor = new CSprite(1712, 0, 0, cursor_tex->getWidth(), cursor_tex->getHeight(), cursor_tex);
	cursorPos.x = 75.0f;
	cursorPos.y = 110.0f;
}

void CGameOverScene::Unload()
{
}

void CGameOverScene::Update(DWORD dt)
{
}

void CGameOverScene::Render()
{
	CGame::GetInstance()->Draw(113.0f, 113.0f, background);
	cursor->Draw(cursorPos.x, cursorPos.y);
}
