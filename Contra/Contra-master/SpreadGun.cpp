#include "SpreadGun.h"
#include "Bill.h"
#include "BillBullet.h"
extern CBill* bill;
float CSpreadGun::DirectionY[5] = {0.25f, 0.12f, 0.0f, -0.12f, -0.25f};
float CSpreadGun::DirectionX[5] = { 0.5f, 0.25f, 0.0f, -0.25f, -0.5f };
void CSpreadGun::Shoot()
{
	float x = bill->GetX();
	float y = bill->GetY();

	if (GetTickCount64() - recoil_check < SPREAD_RECOIL_TIME)
		return;
	if (GetTickCount64() - lastShotTime < SPREA_RELOAD_TIME)
		return;
	recoil_check = GetTickCount64();
	for (int i = 0; i < 10; i++)
	{
		int direction = rand() % 5;
		if (bill->faceDirection == 1)
			if (bill->GetState() == BILL_STATE_LAYDOWN)
				CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x + 15.0f, y + 0.0f, 0.5f, DirectionY[direction] + 0.0f));
			else
				if (bill->GetState() == BILL_STATE_RUN)//Run shot
				{
					if (bill->shotDirection == 1)//Run shot up
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x + 5.0f, y - 10.0f, 0.5f, DirectionY[direction] + -0.5f));
					if (bill->shotDirection == -1)
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x + 8.0f, y + 6.0f, 0.5f, DirectionY[direction] + 0.5f));
					if (bill->shotDirection == 0)
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x + 8.0f, y - 6.0f, 0.5f, DirectionY[direction] + 0.0f));
				}
				else
					if (bill->shotDirection == 1)
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x + 5.0f, y - 15.0f, DirectionY[direction] + 0, DirectionY[direction] + -0.5f));
					else
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x + 8.0f, y - 6.0f, 0.5f, DirectionY[direction] + 0.0f));
		else
			if (bill->GetState() == BILL_STATE_LAYDOWN)
				CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x - 15.0f, y + 0.0f, -0.5f, DirectionY[direction] + 0.0f));
			else
				if (bill->GetState() == BILL_STATE_RUN)
				{
					if (bill->shotDirection == 1)//run shot up
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x - 3.0f, y - 10.0f, -0.5f, DirectionY[direction] + -0.5f));
					if (bill->shotDirection == -1) // run shot down
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x - 10.0f, y + 6.0f, -0.5f, DirectionY[direction] + 0.5f));
					if (bill->shotDirection == 0)
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x - 8.0f, y - 6.0f, -0.5f, DirectionY[direction] + 0.0f));
				}
				else
					if (bill->shotDirection == 1)
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x - 5.0f, y - 15.0f, 0, DirectionY[direction] == -0.5f? -0.5f: DirectionY[direction] - 0.5f));
					else
						CGame::GetInstance()->gameObjects.push_back(new CBillBullet(x - 8.0f, y - 6.0f, -0.5f, DirectionY[direction] + 0.0f));
	}
	if (MagCap <= 1)
	{
		MagCap = 2;
		lastShotTime = GetTickCount64();
	}
	else
		MagCap -= 1;
}
