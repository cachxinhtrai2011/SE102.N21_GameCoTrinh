#pragma once
#include <dinput.h>
#define KEY_CLICK 0
#define KEY_DOWN 1
#define KEY_UP 2
class CInput
{
protected:
	int key;
	int type;
public:
	CInput(int keyCode, int keyType) { key = keyCode; type = keyType; }
	int GetType() { return type; }
	int GetInput() { return key; }
};

typedef CInput* LPCINPUT;
