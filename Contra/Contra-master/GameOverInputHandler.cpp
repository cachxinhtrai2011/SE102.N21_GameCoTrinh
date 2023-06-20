#include "GameOverInputHandler.h"
extern int done;
void CGameOverInputHandler::onKeyClick(int keyCode)
{
}

void CGameOverInputHandler::onKeyPress(int keyCode)
{
	if (keyCode == DIK_UPARROW)
		scene->SetCusorPos(75.0f, 110.0f);
	if (keyCode == DIK_DOWNARROW)
		scene->SetCusorPos(75.0f, 95.0f);
	if (keyCode == DIK_RETURN)
	{
		D3DXVECTOR2 cursorPos;
		scene->GetCursorPos(cursorPos.x, cursorPos.y);
		if (cursorPos.y == 110.0f)
			CGame::GetInstance()->InitiateSwitchScene(2);
		else
			done = 1;
	}
}

void CGameOverInputHandler::onKeyRelease(int keyCode)
{
}

void CGameOverInputHandler::HandleInput(CInput* input)
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
