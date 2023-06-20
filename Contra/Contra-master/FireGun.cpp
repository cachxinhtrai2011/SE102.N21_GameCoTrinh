#include "FireGun.h"
#include "FireBullet.h"
#include "Bill.h"
extern CBill* bill;
void CFireGun::Shoot()
{
	float left, top, right, bottom;
	bill->GetBoundingBox(left, top, right, bottom);
	if (bill->faceDirection == 1)
		if (bill->GetState() == BILL_STATE_LAYDOWN)
			CFireBullet::GetInstance(right, (top + bottom) / 2, 0.5f, 0.0f);
		else
			if (bill->GetState() == BILL_STATE_RUN)//Run shot
			{
				if (bill->shotDirection == 1)//Run shot up
					CFireBullet::GetInstance(right, top - 6.0f, 0.5f, 0.5f);
				if (bill->shotDirection == -1)
					CFireBullet::GetInstance(right, bottom + 10.0f, 0.5f, -0.5f);
				if (bill->shotDirection == 0)
					CFireBullet::GetInstance(right, (top + bottom) / 2, 0.5f, 0.0f);
			}
			else
				if (bill->shotDirection == 1)
					CFireBullet::GetInstance((right + left) / 2, top, 0, 0.5f);
				else
					CFireBullet::GetInstance(right, (top + bottom) / 2 + 4.0f, 0.5f, 0.0f);
	else
		if (bill->GetState() == BILL_STATE_LAYDOWN)
			CFireBullet::GetInstance(left, (top + bottom) / 2, -0.5f, 0.0f);
		else
			if (bill->GetState() == BILL_STATE_RUN)
			{
				if (bill->shotDirection == 1)//run shot up
					CFireBullet::GetInstance(left, top - 6.0f, -0.5f, 0.5f);
				if (bill->shotDirection == -1) // run shot down
					CFireBullet::GetInstance(right, bottom + 10.0f, -0.5f, -0.5f);
				if (bill->shotDirection == 0)
					CFireBullet::GetInstance(left, (top + bottom) / 2, -0.5f, 0.0f);
			}
			else
				if (bill->shotDirection == 1)
					CFireBullet::GetInstance((right + left) / 2, top, 0.0f, 0.5f);
				else
					CFireBullet::GetInstance(right, (top + bottom) / 2 + 4.0f, -0.5f, 0.0f);
}