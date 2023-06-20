#pragma once
#include "InputHandler.h"
#include "GameOverScene.h"
class CGameOverInputHandler: public CInputHandler
{
protected:
	CGameOverScene* scene;
	void onKeyClick(int keyCode);
	void onKeyPress(int keyCode);
	void onKeyRelease(int keyCode);
public:
	CGameOverInputHandler(CGameOverScene* gameover)
	{
		scene = gameover;
	}
	void HandleInput(CInput* input);
};

