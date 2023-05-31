#pragma once
#include "Bullet.h"
class CGun
{
protected:
	int lastShotTime;
public:
	CGun() { lastShotTime = GetTickCount64(); }
	virtual void Shoot() { return; };
};

