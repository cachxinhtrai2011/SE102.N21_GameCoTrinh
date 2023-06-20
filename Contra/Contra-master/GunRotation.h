#pragma once
#include "GameObject.h"
#include "AssetID.h"
#include "ObjectExplosion.h"

#define GUN_ROTATION_DELAY 1000
class CGunRotation : public CGameObject
{
	ULONG lastTurn;
	float radius;
	float lastShoot;
public:
	CGunRotation(float x, float y) : CGameObject(x, y) { state = GUNROTATION_STATE_HIDDEN; lastTurn = -1; radius = PI; hp = 9999999; lastShoot = -1; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject = NULL);
	void Render();
	static void LoadAnimation();
	void SetState(int state);
	int IsCollidable() { return 1; };
	void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking() { return 1; };
	void GetHit(int damage);

};
