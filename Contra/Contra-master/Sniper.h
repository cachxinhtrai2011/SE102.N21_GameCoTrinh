#pragma once
#include "GameObject.h";
#include "AssetID.h";
class CSniper: public CGameObject
{
protected:
	int faceDirection = -1;
public:
	CSniper(float x, float y) : CGameObject(x, y) { state = SNIPER_STATE_NORMAl; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject);
	void Render();
	static void LoadAnimation();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; }
	// When no collision has been detected (triggered by CCollision::Process)
	void OnNoCollision(DWORD dt);

	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(LPCOLLISIONEVENT e);
};

