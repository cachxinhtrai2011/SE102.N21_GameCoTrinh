#pragma once
#include "Gun.h"
#define SPREAD_RECOIL_TIME 50
#define SPREA_RELOAD_TIME 300
class CSpreadGun:public  CGun
{
	ULONG lastShotTime;
	ULONG recoil_check;
	static float DirectionX[5];
	static float DirectionY[5];
	int MagCap = 2;
public:
	void Shoot();
};

