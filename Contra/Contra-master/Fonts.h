#pragma once
#include "Font.h"
class CFonts
{
	static CFonts* __instance;

	unordered_map<int, CFont*> fonts;

public:
	void Add(int id, CFont* font);
	CFont* Get(int id);

	static CFonts* GetInstance();

	void Clear();
};

