#pragma once
#include "Animations.h"
#include "Textures.h"
#include <string>
#include <string.h>
class CFont
{
private:
	int id;
	LPCWSTR FontFilePath;
	unordered_map<char, CSprite*> charSet;
	int charWidth;
	int charHeight;
public:
	CFont(int id, LPCWSTR filePath)
	{
		this->id = id;
		this->FontFilePath = filePath;
	}
	void LoadFont(int width, int height, int charPerRow)
	{
		charWidth = width;
		charHeight = height;
		CTextures::GetInstance()->Add(id, FontFilePath);
		CTexture* tex = CTextures::GetInstance()->Get(id);
		for (int i = 0; i < 26; i++)
			charSet[char(97 + i)] = new CSprite(97 + i, (i * (width + 2)) % (tex->getWidth()), i / charPerRow * (height + 2), (i * (width + 2) + width)%(tex->getWidth()), i / charPerRow * (height + 2) + height + 1, tex);
		for(int i = 0; i < 10 ; i++)
			charSet[char(48 + i)] = new CSprite(48 + i, (i + 26) * (width + 2), (i + 26) / charPerRow * (height + 2), (i + 26) * (width + 2) + width, (i + 26) / charPerRow * (height + 2) + height, tex);
		charSet[char(32)] = new CSprite(32, tex->getWidth() - width, tex->getHeight() - height, tex->getWidth(), tex->getHeight(), tex);
	}

	void DrawString(string string, float x, float y)
	{
		int length = string.length();
		for (int i = 0; i < length; i++)
			charSet[string[i]]->Draw(x + i * (charWidth + 2), y);
	}
};