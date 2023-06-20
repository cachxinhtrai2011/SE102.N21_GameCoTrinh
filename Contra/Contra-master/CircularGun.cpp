#include "CircularGun.h"
#include "Bill.h"
#include "CurcularBullet.h"
#include "FireBullet.h"
extern CBill* bill;
void CCircularGun::Shoot()
{
	float left, top, right, bottom;
	bill->GetBoundingBox(left, top, right, bottom);
	if (GetTickCount64() - lastShotTime < RECOIL_TIME)
		return;
	lastShotTime = GetTickCount64();
	if (bill->faceDirection == 1)
		if(bill->GetState() == BILL_STATE_LAYDOWN)
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(right, (top + bottom) / 2, 0.12f, 0.0f));
		else if (bill->GetState() == BILL_STATE_RUN)//Run shot
		{
			if (bill->shotDirection == 1)//Run shot up
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(right, top - 6.0f, 0.12f, 0.12f));
			if (bill->shotDirection == -1)
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(right, bottom + 10.0f, 0.12f, -0.12f));
			if (bill->shotDirection == 0)
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(right, (top + bottom) / 2, 0.12f, 0.0f));
		}
		else
			if (bill->shotDirection == 1)
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet((right + left) / 2, top, 0, 0.12f));
			else
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(right, (top + bottom) / 2 + 4.0f, 0.12f, 0.0f));
	else
		if (bill->GetState() == BILL_STATE_LAYDOWN)
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(left, (top + bottom) / 2, -0.12f, 0.0f));
		else if (bill->GetState() == BILL_STATE_RUN)
		{
			if (bill->shotDirection == 1)//run shot up
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(left, top - 6.0f, -0.12f, 0.12f));
			if (bill->shotDirection == -1) // run shot down
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(right, bottom + 10.0f, -0.12f, -0.12f));
			if (bill->shotDirection == 0)
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(left, (top + bottom) / 2, -0.12f, 0.0f));
		}
		else
			if (bill->shotDirection == 1)
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet((right + left) / 2, top, 0, 0.12f));
			else
				((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetAmmo()->push_back(new CCurcularBullet(right, (top + bottom) / 2, -0.12f, 0.0f));
}
