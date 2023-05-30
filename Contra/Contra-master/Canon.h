#pragma once
#include "GameObject.h"
#include "AssetID.h"

#define CANON_ROTATION_DELAY 1000
class CCanon : public CGameObject
{
private:
	ULONG lastTurn;
	float radius;
public:

	CCanon(float x, float y) : CGameObject(x, y) { state = CANON_STATE_HIDDEN; lastTurn = -1; radius = PI; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject = NULL);
	void Render();
	static void LoadAnimation();
	void SetState(int state);
	int IsCollidable() { return 1; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking() { return 1; }
};

