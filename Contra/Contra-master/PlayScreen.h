#pragma once
#include "Scene.h"
#include "Map.h"
#include "QuadTree.h"
#define CAM_CHANGE_TIME		30

class CBullet;
class CPlayScene : public CScene
{
protected:
	int paused;
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	CMap* current_map = NULL;
	vector<LPGAMEOBJECT> objects;
	LPTREENODE QuadTree;
	vector<CBullet*>* ammo;
	CScene* pauseScene = NULL;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_TILEMAP_DATA(string line);
	void _ParseSection_TILEMAP_HIDDEN_DATA(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void LoadAssets(LPCWSTR assetFile);

public:
	void AddObject(LPGAMEOBJECT object);
	CPlayScene(int id, LPCWSTR filePath);
	//vector<LPGAMEOBJECT> GetListObject() { return objects; }
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	CMap* GetMap() { return current_map; }
	void Clear();
	void PurgeDeletedObjects();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void AddObjectToQuadTree(LPGAMEOBJECT obj) { QuadTree->AddObjectToNode(obj); }
	int IsPaused() { return paused; }
	vector<CBullet*>* GetAmmo() { return ammo; }
	LPGAMEOBJECT GetPlayer() { return player;  }
};

typedef CPlayScene* LPPLAYSCENE;