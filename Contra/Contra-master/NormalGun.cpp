#include "NormalGun.h"
#include "Bill.h"
#include "BillBullet.h"
#include "FireBullet.h"
#include "PlayScreen.h"
extern CBill* bill;
void CNormalGun::Shoot()
{
	float top, left, right, bottom;
	bill->GetBoundingBox(left, top, right, bottom);

	if (GetTickCount64() - lastShotTime < NORMAL_GUN_RECOIL_TIME)
		return;
	lastShotTime = GetTickCount64();
	if (bill->faceDirection == 1)
		if (bill->GetState() == BILL_STATE_LAYDOWN)
			((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(right,((top + bottom) / 2), 0.35f, 0.0f));
		else 
			if (bill->GetState() == BILL_STATE_RUN)//Run shot
			{
				if (bill->shotDirection == 1)//Run shot up
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(right, top - 6.0f, 0.35f, 0.35f));
				if (bill->shotDirection == -1)
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(right, bottom + 10.0f, 0.35f, -0.35f));
				if (bill->shotDirection == 0)
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet( right, bottom + (top - bottom) / 2 + 6.0f, 0.35f, 0.0f));
			}
			else
				if (bill->shotDirection == 1)
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(left + (right - left) / 2, top,  0, 0.35f));
				else
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(right, (top + bottom)/2 + 6.0f, 0.35f, 0.0f));
	else
		if(bill->GetState() == BILL_STATE_LAYDOWN)
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(left, bottom + (top - bottom) / 2,  -0.35f, 0.0f));
		else
			if (bill->GetState() == BILL_STATE_RUN)
			{
				if (bill->shotDirection == 1)//run shot up
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(left, top - 6.0f,  -0.35f, 0.35f));
				if (bill->shotDirection == -1) // run shot down
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(right, bottom + 10.0f,  -0.35f, -0.35f));
				if (bill->shotDirection == 0)
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(left, bottom + (top - bottom) / 2 + 6.0f, -0.35f, 0.0f));
			}
			else
				if (bill->shotDirection == 1)
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(left + (right - left) / 2, top, 0, 0.35f));
				else
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CBillBullet(left, bottom + (top - bottom) / 2 + 6.0f, -0.35f, 0.0f));
}	