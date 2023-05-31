#include "RifleGun.h"
#include "RifleBullet.h"
#include "Bill.h"

extern CBill* bill;
void CRifleGun::Shoot()
{
	float x = bill->GetX();
	float y = bill->GetY();

	if (GetTickCount64() - recoil_check < RIFLE_RECOIL_TIME)
		return;
	if (GetTickCount64() - lastShotTime < RIFLE_RELOAD_TIME)
		return;
	recoil_check = GetTickCount64();
	for (int i = 0; i < 10; i++)
	{
		int direction = rand() % 5;
		if (bill->faceDirection == 1)
			if (bill->GetState() == BILL_STATE_LAYDOWN)
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x + 15.0f, y - 0.0f, 0.35f, 0.0f));
			else
				if (bill->GetState() == BILL_STATE_RUN)//Run shot
				{
					if (bill->shotDirection == 1)//Run shot up
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x + 5.0f, y + 10.0f, 0.35f, 0.35f));
					if (bill->shotDirection == -1)
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x + 8.0f, y - 6.0f, 0.35f, -0.35f));
					if (bill->shotDirection == 0)
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x + 8.0f, y + 6.0f, 0.35f, 0.0f));
				}
				else
					if (bill->shotDirection == 1)
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x + 5.0f, y - 15.0f, 0, 0.35f));
					else
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x + 8.0f, y + 6.0f, 0.35f,  0.0f));
		else
			if (bill->GetState() == BILL_STATE_LAYDOWN)
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x - 15.0f, y + 0.0f, -0.35f, 0.0f));
			else
				if (bill->GetState() == BILL_STATE_RUN)
				{
					if (bill->shotDirection == 1)//run shot up
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x - 3.0f, y + 10.0f, -0.35f, 0.35f));
					if (bill->shotDirection == -1) // run shot down
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x - 10.0f, y - 6.0f, -0.35f, -0.35f));
					if (bill->shotDirection == 0)
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x - 8.0f, y + 6.0f, -0.35f, 0.0f));
				}
				else
					if (bill->shotDirection == 1)
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x - 5.0f, y + 15.0f, 0, 0.35f));
					else
						((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CRifleBullet(x - 8.0f, y + 6.0f, -0.35f, 0.0f));
	}
	if (MagCap <= 1)
	{
		MagCap = 2;
		lastShotTime = GetTickCount64();
	}
	else
		MagCap -= 1;
}
