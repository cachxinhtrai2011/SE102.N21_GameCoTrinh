#pragma once
#include "GameObject.h"
#include "AssetID.h"

#define GUN_ROTATION_DELAY 1000
class CGunRotation : public CGameObject
{
	ULONG lastTurn;
	float radius;
public:
	CGunRotation(float x, float y) : CGameObject(x, y) { state = GUNROTATION_STATE_HIDDEN; lastTurn = -1; radius = PI; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject = NULL);
	void Render();
	static void LoadAnimation();
	void SetState(int state);
	int IsCollidable() { return 1; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking() { return 1; }
};
