#pragma once
#include "Scene.h"
#include "Text.h"
#include <string>
#include <string.h>
#define INTRO_DURATION 40000
class CIntroScene: public CScene
{
protected:
	int introDuration;
	CTexture* background;
	vector<CText*> texts;
public:
	CIntroScene(int id, LPCWSTR filePath) :CScene(id, filePath) {
		background = NULL;
	}
	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();
	void AddText(CText* text);
	void _ParseSection_BACKGROUND(string line);
	void _ParseSection_TEXT(string line);
};

