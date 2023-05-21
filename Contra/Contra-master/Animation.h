#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Sprites.h"
#include "AnimationFrame.h"


using namespace std;

class CAnimation
{
	CAnimation* startAnimation;
	CAnimation* endAnimation;
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	BOOL oneTimeAnimation;
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; startAnimation = NULL; endAnimation = NULL; oneTimeAnimation = false; }
	void Add(int spriteId, DWORD time = 0);
	void SetStartAnimation(CAnimation* ani) { startAnimation = ani; }
	void SetEndAnimation(CAnimation* ani) { endAnimation = ani; }
	void Render(float x, float y, float rotationDeg = 0.0f);
};

typedef CAnimation* LPANIMATION;