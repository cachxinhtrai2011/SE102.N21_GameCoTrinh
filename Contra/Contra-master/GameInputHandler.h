#pragma once
#include "InputHandler.h"
#include "GameOverScene.h"
#include "StartScene.h"
class CGameInputHandler: public CInputHandler
{
	/*int current_scene = -1;
	int next_scene = 0;*/
protected:
	CGameOverScene* OverScene;
	CStartScene* StartScene;
	
	void onKeyClick(int keyCode);
	void onKeyPress(int keyCode);
	void onKeyRelease(int keyCode);
public:
	CGameInputHandler(CGameOverScene* gameover)
	{
		OverScene = gameover;
	}
	void HandleInput(CInput* input);
	CGameInputHandler(CStartScene* startscene)
	{
		StartScene = startscene;
	}
};

