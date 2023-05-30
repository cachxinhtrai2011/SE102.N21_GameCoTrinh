#pragma once
#include "Game.h"
#include "AssetID.h"

class CBullet : public CGameObject
{
protected:
	LPANIMATION bulletAnimation;
public:
	CBullet(float x, float y, float vx = 0.5f, float vy = 0.0f) :CGameObject(x,y){

			this->vy = vy;
			this->vx = vx;
			bulletAnimation = NULL;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject = NULL) {
		x += vx * dt;
		y += vy * dt;

		//Delete object if 
		if (x < 0 || y < 0)
			return;
		CGame* game = CGame::GetInstance();
		float camX, camY;
		CGame::GetInstance()->GetCamPos(camX, camY);
		float camWidth, camHeight;
		camWidth = CGame::GetInstance()->GetScreenWidth();
		camHeight = CGame::GetInstance()->GetScreenHeight();
		if (x < camX || x > camX + camWidth + 50 || y < camY || y > camY + camHeight + 50)
			DeleteBullet();
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
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};