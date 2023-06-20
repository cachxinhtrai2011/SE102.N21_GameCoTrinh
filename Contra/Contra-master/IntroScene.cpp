#include "IntroScene.h"
#include "AssetID.h"
#include <iostream>
#include <fstream>
#include "Game.h"
#include "Utils.h"
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_BACKGROUND	1
#define SCENE_SECTION_TEXT	2
#define MAX_SCENE_LINE 1024

using namespace std;

void CIntroScene::Load()
{
	//DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);
	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[BACKGROUND]") { section = SCENE_SECTION_BACKGROUND; continue; };
		if (line == "[TEXT]") { section = SCENE_SECTION_TEXT; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_BACKGROUND: _ParseSection_BACKGROUND(line); break;
		case SCENE_SECTION_TEXT: _ParseSection_TEXT(line); break;

		}
	}
	f.close();
	introDuration = GetTickCount64();
}

void CIntroScene::Unload()
{
}

void CIntroScene::Update(DWORD dt)
{
	CGame::GetInstance()->InitiateSwitchScene(1);
	if (GetTickCount64() - introDuration >= INTRO_DURATION)
		CGame::GetInstance()->SwitchScene();
}

void CIntroScene::Render()
{
	CGame::GetInstance()->Draw(113.0f, 113.0f, background);
	for (int i = 0; i < texts.size(); i++)
		texts.at(i)->Render();
}
void CIntroScene::AddText(CText* text)
{
	texts.push_back(text);
}

void CIntroScene::_ParseSection_BACKGROUND(string line) {
	background = CGame::GetInstance()->LoadTexture(wstring(line.begin(), line.end()).c_str());
}
void CIntroScene::_ParseSection_TEXT(string line) {
	vector<string> tokens = split(line);
	int x = atoi(tokens[1].c_str());
	int y = atoi(tokens[2].c_str());
	CText* tex = new CText(x, y, tokens[0], 0);
	AddText(tex);
}