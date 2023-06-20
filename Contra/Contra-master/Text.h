#pragma once
#include "Fonts.h"
#include "GameObject.h"

class CText: public CGameObject
{
protected:
	string text;
	int fontId;
public:
	CText(float x, float y, string text, int font):CGameObject(x,y) {
		this->text = text;
		fontId = font;
	}
	void Render()
	{
		CFonts::GetInstance()->Get(fontId)->DrawString(text, x, y);
	}
};

