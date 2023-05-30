#pragma once
#include "Gun.h"
#define RECOIL_TIME 200
class CCircularGun: public CGun
{
private:
	ULONG lastBulletTime;
public:
	CCircularGun() : CGun() {
		lastBulletTime = GetTickCount64();
	}
	void Shoot();
};

