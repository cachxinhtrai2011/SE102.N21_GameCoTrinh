#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "Animations.h"
#include "Collision.h"
#include "Textures.h"
using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGame;
class CGameObject
{
protected:
	float x; 
	float y;

	float vx;
	float vy;

	int nx;	 
	int state;
	int Deleted = 0;
	int dieStart = 0;
	int hp;
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeedX(float vx) { this->vx = vx; }
	void SetSpeedY(float vy) { this->vy = vy; }
	void SetState(int state) { this->state = state; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	int GetState() { return this->state; }

	CGameObject();
	CGameObject(float x, float y) :CGameObject() { this->x = x; this->y = y; this->vx = 0; this->vy = 0; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject = NULL) {}
	virtual void HandleInput() {};
	virtual void Render() = 0;
	virtual void DeleteFromGameObjects();
	virtual void GetHit(int damage = 0) {}
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	float GetX() { return x; }
	virtual int IsEnemy() { return 1; }
	float GetY() { return y; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt = 0) {};
	virtual int IsBlocking() { return 0; };


	void RenderBoundingBox();
	int IsDeleted() { return Deleted; }
	void SetDeleted(int del) { Deleted = del; }
	~CGameObject(); 
};

typedef CGameObject* LPGAMEOBJECT;