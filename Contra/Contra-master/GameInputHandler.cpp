#include "GameInputHandler.h"
extern int done;
void CGameInputHandler::onKeyClick(int keyCode)
{
}

void CGameInputHandler::onKeyPress(int keyCode)
{
	//Game Over
	if (keyCode == DIK_UPARROW)
		OverScene->SetCusorPos(75.0f, 110.0f);
	if (keyCode == DIK_DOWNARROW)
		OverScene->SetCusorPos(75.0f, 95.0f);
	if (keyCode == DIK_RETURN)
	{
		if (CGame::GetInstance()->GetCurrentSceneID() == 00)
		{
			CGame::GetInstance()->InitiateSwitchScene(CGame::GetInstance()->GetCurrentSceneID() + 1);
		}
		else {
			D3DXVECTOR2 cursorPos;
			OverScene->GetCursorPos(cursorPos.x, cursorPos.y);
			//StartScene->GetCursorPos(cursorPos.x, cursorPos.y);
			if (cursorPos.y == 110.0f)
				CGame::GetInstance()->InitiateSwitchScene(1);
			else
				done = 1;

		}
		
	}
}

void CGameInputHandler::onKeyRelease(int keyCode)
{
}

void CGameInputHandler::HandleInput(CInput* input)
{
	switch (input->GetType())
	{
	case KEY_CLICK:
		onKeyClick(input->GetInput());
		break;
	case KEY_DOWN:
		onKeyPress(input->GetInput());
		break;
	case KEY_UP:
		onKeyRelease(input->GetInput());
		break;
	default:
		break;
	}
}
