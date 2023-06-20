#include "Fonts.h"

CFonts* CFonts::__instance = NULL;
void CFonts::Add(int id, CFont* font)
{
	fonts[id] = font;
	font->LoadFont(6, 6, 6);
}

CFont* CFonts::Get(int id)
{
	return fonts[id];
}

CFonts* CFonts::GetInstance()
{
	if (__instance == NULL) __instance = new CFonts();
	return __instance;
}

void CFonts::Clear()
{
	__instance == NULL;
	fonts.clear();
}
