#pragma once
#include "Game.h"
#include "AssetID.h"
class CBullet : public CGameObject
{
protected:
	LPANIMATION bulletAnimation;
	int isEnemy;
public:
	virtual int GetDamage() { return 0; }
	CBullet(float x, float y, float vx = 0.5f, float vy = 0.0f, int enemy = 0) :CGameObject(x,y){

			this->vy = vy;
			this->vx = vx;
			bulletAnimation = NULL;
			isEnemy = enemy;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject = NULL) 
	{
		CCollision::GetInstance()->Process(this, dt, gameObject);
	}
	void Render() { 
		if (bulletAnimation != NULL)
			bulletAnimation->Render(x, y);
	}
	void DeleteBullet()
	{
		vector<CBullet*>* ammo = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo();
		vector<CBullet*>::iterator i = std::find(ammo->begin(), ammo->end(), this);
		ammo->erase(i);
	}
	static void LoadAnimation()
	{
		CTextures* tex = CTextures::GetInstance();
		tex->Add(ID_BULLET_TEXTURE, TEXTURE_BULET_PATH);
	}

	int IsCollidable() { return 1; };
	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	int IsEnemy() { return isEnemy; }
};