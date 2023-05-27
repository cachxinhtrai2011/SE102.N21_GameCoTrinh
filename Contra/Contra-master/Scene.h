#pragma once

#include "InputHandler.h"
#include "GameObject.h"
/*
*  Abstract class for a game scene
*/

class CScene
{
protected:
	CInputHandler* key_handler;
	int id;
	LPCWSTR sceneFilePath;

public:
	CScene(int id, LPCWSTR filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
		this->key_handler = NULL;
	}
	int GetIdScene() { return id; }
	CInputHandler* GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual LPGAMEOBJECT GetPlayer() { return NULL;  }
};
typedef CScene* LPSCENE;


class CSceneKeyHandler : public CInputHandler
{
protected:
	CScene* scence;

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CInputHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;