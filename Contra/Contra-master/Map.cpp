#include "Map.h"
#include "Utils.h"
#include "Game.h"
#include "debug.h"
CMap::CMap(int TileSetID, int TotalRowsOfMap, int TotalColumnsOfMap, int TotalRowsOfTileSet, int  TotalColumnsOfTileSet, int TotalTiles, int startX, int startY)
{
	TileSet = CTextures::GetInstance()->Get(TileSetID);
	this->TotalRowsOfMap = TotalRowsOfMap;
	this->TotalColumnsOfMap = TotalColumnsOfMap;
	this->TotalRowsOfTileSet = TotalRowsOfTileSet;
	this->TotalColumnsOfTileSet = TotalColumnsOfTileSet;
	this->TotalTiles = TotalTiles;
	this->startX = startX;
	this->startY = startY;
	CamX = CamY = 0;
	TileMap = NULL;
}

CMap::~CMap()
{
}
bool CMap::checkObjectInCamera(float x, float y) {
	float w = 32.0f;
	float h = 32.0f;
	if (x + w <= (CGame::GetInstance()->GetCamX()) || (CGame::GetInstance()->GetCamX()) + SCREEN_WIDTH <= x)
		return false;
	if (y + h <= (CGame::GetInstance()->GetCamY()) || (CGame::GetInstance()->GetCamY()) + SCREEN_HEIGHT + h <= y)
		return false;
	return true;
}
D3DXVECTOR2 CMap::setWorldToSceen(D3DXVECTOR2 R_position)
{
	CGame* game = CGame::GetInstance();
	D3DXVECTOR3 position(R_position.x, R_position.y, 1);

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -game->GetCamX();  // vpx = x0
	mt._42 = game->GetCamY();  // vpy = y0

	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);
	//  vp_pos = position * mt  (  position : world position of object)


	//these code bellow to draw the sprite, will use in the future
	/*D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	_SpriteHandler->Draw(
		_Image,
		&srect,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
	);*/

	return D3DXVECTOR2(vp_pos.x, vp_pos.y);
}
void CMap::Render()
{
	int FirstColumn = int(floor(CamX / TILE_WIDTH));
	//int LastColumn = int(ceil((CamX * TILE_WIDTH + CGame::GetInstance()->GetScreenWidth()) / TILE_WIDTH));
	int LastColumn = TotalColumnsOfMap;
	if (LastColumn >= TotalColumnsOfMap)
		LastColumn = TotalColumnsOfMap - 1;
	int d = 0;
	for (int CurrentRow = 0; CurrentRow < TotalRowsOfMap; CurrentRow++)
		for (int CurrentColumn = FirstColumn; CurrentColumn <= LastColumn; CurrentColumn++)
		{
			int index = TileMap[CurrentRow][CurrentColumn] - 1;
			if (index < TotalTiles)
			{
				float xDraw = float(CurrentColumn * TILE_WIDTH) + float(startX * TILE_WIDTH);
				float yDraw = float((this->TotalRowsOfMap - CurrentRow )* TILE_HEIGHT) - float(startY * TILE_HEIGHT);
				//if (checkObjectInCamera(xDraw, yDraw)) {
					Tiles.at(index)->Draw(xDraw - 9.0f , yDraw - 1.0f);
				//}
			}
		}

	//for (int CurrentRow = TotalRowsOfMap - 1; CurrentRow >= 0; CurrentRow--)
	//	for (int CurrentColumn = FirstColumn; CurrentColumn <= LastColumn; CurrentColumn++)
	//	{
	//		int index = TileMap[CurrentRow][CurrentColumn] - 1;
	//		if (index < TotalTiles)
	//		{
	//			float xDraw = float(CurrentColumn * TILE_WIDTH) + float(startX * TILE_WIDTH);
	//			float yDraw = float(CurrentRow * TILE_HEIGHT) - float(startY * TILE_HEIGHT);
	//			//if (checkObjectInCamera(xDraw, yDraw)) {
	//			D3DXVECTOR2 pos = setWorldToSceen(D3DXVECTOR2(xDraw, yDraw));
	//			Tiles.at(index)->Draw(xDraw -9.0f,pos.y - 9);
	//			//}
	//		}
	//	}

}

void CMap::SetTileMapData(int** TileMapData)
{
	TileMap = TileMapData;
}


void CMap::ExtractTileFromTileSet()
{
	for (int TileNum = 0; TileNum < TotalTiles; TileNum++)
	{
		int left = TileNum % TotalColumnsOfTileSet * TILE_WIDTH;
		int top = TileNum / TotalColumnsOfTileSet * TILE_HEIGHT;
		int right = left + TILE_WIDTH;
		int bottom = top + TILE_HEIGHT;
		LPSPRITE NewTile = new CSprite(TileNum, left, top, right, bottom, TileSet); // get tile from tileset
		this->Tiles.push_back(NewTile);
	}
}

int CMap::GetMapWidth()
{
	return TotalColumnsOfMap * TILE_WIDTH;
}

int CMap::GetMapHeight()
{
	//DebugOut("");
	return TotalRowsOfMap * TILE_HEIGHT;
}