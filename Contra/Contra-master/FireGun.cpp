#include "FireGun.h"
#include "FireBullet.h"
#include "Bill.h"
extern CBill* bill;
void CFireGun::Shoot()
{
	float x = bill->GetX();
	float y = bill->GetY();
	if (bill->faceDirection == 1)
		if (bill->GetState() == BILL_STATE_LAYDOWN)
			CFireBullet::GetInstance(x + 15.0f, y + 0.0f, 1.0f, 0.0f);
		else
			if (bill->GetState() == BILL_STATE_RUN)//Run shot
			{
				if (bill->shotDirection == 1)//Run shot up
					CFireBullet::GetInstance(x + 5.0f, y - 10.0f, 1.0f, -1.0f);
				if (bill->shotDirection == -1)
					CFireBullet::GetInstance(x + 8.0f, y + 6.0f, 1.0f, 1.0f);
				if (bill->shotDirection == 0)
					CFireBullet::GetInstance(x + 8.0f, y - 6.0f, 1.0f, 0.0f);
			}
			else
				if (bill->shotDirection == 1)
					CFireBullet::GetInstance(x + 5.0f, y - 15.0f, 0, -1.0f);
				else
					CFireBullet::GetInstance(x + 8.0f, y - 6.0f, 1.0f, 0.0f);
	else
		if (bill->GetState() == BILL_STATE_LAYDOWN)
			CFireBullet::GetInstance(x - 15.0f, y + 0.0f, -1.0f, 0.0f);
		else
			if (bill->GetState() == BILL_STATE_RUN)
			{
				if (bill->shotDirection == 1)//run shot up
					CFireBullet::GetInstance(x - 3.0f, y - 10.0f, -1.0f, -1.0f);
				if (bill->shotDirection == -1) // run shot down
					CFireBullet::GetInstance(x - 10.0f, y + 6.0f, -1.0f, 1.0f);
				if (bill->shotDirection == 0)
					CFireBullet::GetInstance(x - 8.0f, y - 6.0f, -1.0f, 0.0f);
			}
			else
				if (bill->shotDirection == 1)
					CFireBullet::GetInstance(x - 5.0f, y - 15.0f, 0, -1.0f);
				else
					CFireBullet::GetInstance(x - 8.0f, y - 6.0f, -1.0f, 0.0f);
}