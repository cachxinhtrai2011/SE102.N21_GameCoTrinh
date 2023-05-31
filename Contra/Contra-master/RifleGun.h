#pragma once
#include "Gun.h"
#define RIFLE_RECOIL_TIME 50
#define RIFLE_RELOAD_TIME 200
class CRifleGun:public CGun
{
private:
	ULONG lastShotTime;
	ULONG recoil_check;
	int MagCap = 2;
public:
	void Shoot();
};

