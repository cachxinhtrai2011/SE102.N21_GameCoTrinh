#pragma once
#include "Input.h"
#include <vector>
class CInputHandler
{
protected:
	virtual void onKeyPress(int keyCode) = 0;
	virtual void onKeyRelease(int keyCode) = 0;
	virtual void onKeyClick(int keyCode) = 0;
public:
	static std::vector<int> KeyToListen;
	virtual void HandleInput(CInput* input) = 0;
};
