
#include "Bill.h"
#include "Textures.h"
#include "Game.h"
#include "BillBullet.h"
#include "Soldier.h"
#include "Portal.h"
void CBill::Update(DWORD dt, vector<LPGAMEOBJECT> *gameObject)
{
	if (isShotting)
		gun->Shoot();
	CCollision::GetInstance()->Process(this, dt, gameObject);
}

void CBill::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniID = -1;
	if (state == BILL_STATE_IDLE)
	{
		if (faceDirection == 1)
			if (isShotting)
				if (shotDirection == 1)
					aniID = ID_ANI_BILL_IDLE_SHOT_UP_RIGHT;
				else
					aniID = ID_ANI_BILL_IDLE_RIGHT;
			else
				aniID = ID_ANI_BILL_IDLE_RIGHT;
		else
			if (isShotting)
				if (shotDirection == 1)
					aniID = ID_ANI_BILL_IDLE_SHOT_UP_LEFT;
				else
					aniID = ID_ANI_BILL_IDLE_LEFT;
			else
				aniID = ID_ANI_BILL_IDLE_LEFT;
	}
	else if (state == BILL_STATE_RUN)
	{
		if (faceDirection == 1)
			if (isShotting)
				if (shotDirection == 1)
					aniID = ID_ANI_BILL_RUN_SHOT_UP_RIGHT;
				else if (shotDirection == -1)
					aniID = ID_ANI_BILL_RUN_SHOT_DOWN_RIGHT;
				else aniID = ID_ANI_BILL_RUN_SHOT_RIGHT;
			else
				aniID = ID_ANI_BILL_RUN_RIGHT;
		else
			if (isShotting)
				if (shotDirection == 1)
					aniID = ID_ANI_BILL_RUN_SHOT_UP_LEFT;
				else if (shotDirection == -1)
					aniID = ID_ANI_BILL_RUN_SHOT_DOWN_LEFT;
				else aniID = ID_ANI_BILL_RUN_SHOT_LEFT;
			else
				aniID = ID_ANI_BILL_RUN_LEFT;
	}
	else if (state == BILL_STATE_SWIM || state == BILL_STATE_SWIM_MOVE)
	{
		if (faceDirection == 1)
			if (isShotting)
				if (shotDirection == 1)
					if (vx == 0)
						aniID = ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_RIGHT;
					else
						aniID = ID_ANI_BILL_SWIMMING_SHOT_UP_RIGHT;
				else
					aniID = ID_ANI_BILL_SWIMMING_SHOT_RIGHT;
			else
			{
				aniID = ID_ANI_BILL_SWIMMING_RIGHT;
			}
		else
			if (isShotting)
				if (shotDirection == 1)
					if (vx == 0)
						aniID = ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_LEFT;
					else
						aniID = ID_ANI_BILL_SWIMMING_SHOT_UP_LEFT;
				else
					aniID = ID_ANI_BILL_SWIMMING_SHOT_LEFT;
			else
			{
				aniID = ID_ANI_BILL_SWIMMING_LEFT;

			}
	}
	else if (state == BILL_STATE_DEAD) aniID = ID_ANI_BILL_DEAD;
	else if (state == BILL_STATE_JUMP) if (faceDirection == 1) aniID = ID_ANI_BILL_JUMP_RIGHT; else aniID = ID_ANI_BILL_JUMP_LEFT;
	else if (aniID == -1)
		if (faceDirection == 1) aniID = ID_ANI_BILL_IDLE_RIGHT; else aniID = ID_ANI_BILL_IDLE_LEFT;
	if (state == BILL_STATE_LAYDOWN)
		if (faceDirection == 1)
			aniID = ID_ANI_BILL_LAYDOWN_RIGHT;
		else
			aniID = ID_ANI_BILL_LAYDOWN_LEFT;

	animations->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}

void CBill::SetState(int state)
{
	switch (state)
	{
		case BILL_STATE_IDLE:
			vx = 0;
			isSitting = false;
			break;
		case BILL_STATE_JUMP:
			vy = BILL_JUMP_SPEED_Y;
			isSitting = false;
			break;
		case BILL_STATE_LAYDOWN:
			vx = 0;
			break;
		case BILL_STATE_RUN:
			if (faceDirection == 1)
			{
				vx = BILL_RUN_SPEED;
				isSitting = false;
			}
			else
			{
				vx = -BILL_RUN_SPEED;
				isSitting = false;
			}
			if (state == BILL_STATE_SWIM)
				return;
			break;
		case BILL_STATE_SWIM_MOVE:
			if (faceDirection == 1)
			{
				vx = BILL_RUN_SPEED;
				isSitting = false;
			}
			else
			{
				vx = -BILL_RUN_SPEED;
				isSitting = false;
			}
			break;
		case BILL_STATE_DEAD:
			vx = -BILL_RUN_SPEED;
			vy = BILL_JUMP_SPEED_Y;
		default:
			vx = 0;
			isSitting = false;
	}
	CGameObject::SetState(state);
}

void CBill::LoadAnimation()
{
	CTextures* tex = CTextures::GetInstance();
	tex->Add(TEXTURE_RIGHT_ID, TEXTURE_RIGHT_PATH);
	CSprites* sprite = CSprites::GetInstance();
	CAnimations* animation = CAnimations::GetInstance();
	LPANIMATION ani;
	//Load idle animation
 	sprite->Add(ID_ANI_BILL_IDLE_RIGHT, 1, 30, 25, 65, tex->Get(TEXTURE_RIGHT_ID));
	ani = new CAnimation(DURATION_ANI_BILL_IDLE);
	ani->Add(ID_ANI_BILL_IDLE_RIGHT);
	animation->Add(ID_ANI_BILL_IDLE_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_IDLE_LEFT, 1, 30, 25, 65, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	ani = new CAnimation(DURATION_ANI_BILL_IDLE);
	ani->Add(ID_ANI_BILL_IDLE_LEFT);
	animation->Add(ID_ANI_BILL_IDLE_LEFT, ani);

	//Load idle shot up right animation
	sprite->Add(ID_ANI_BILL_IDLE_SHOT_UP_RIGHT, 51, 19, 66, 65, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_IDLE_SHOT_UP_RIGHT + 1, 67, 19, 82, 65, tex->Get(TEXTURE_RIGHT_ID));

	ani = new CAnimation(DURATION_ANI_BILL_IDLE);
	ani->Add(ID_ANI_BILL_IDLE_SHOT_UP_RIGHT);
	ani->Add(ID_ANI_BILL_IDLE_SHOT_UP_RIGHT + 1);
	animation->Add(ID_ANI_BILL_IDLE_SHOT_UP_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_IDLE_SHOT_UP_LEFT, 51, 19, 66, 65, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	sprite->Add(ID_ANI_BILL_IDLE_SHOT_UP_LEFT + 1, 67, 19, 82, 65, tex->Get(TEXTURE_RIGHT_ID), -1.0f);

	ani = new CAnimation(DURATION_ANI_BILL_RUN);
	ani->Add(ID_ANI_BILL_IDLE_SHOT_UP_LEFT);
	ani->Add(ID_ANI_BILL_IDLE_SHOT_UP_LEFT + 1);

	animation->Add(ID_ANI_BILL_IDLE_SHOT_UP_LEFT,ani);

	//Load run sprites
	sprite->Add(ID_ANI_BILL_RUN_RIGHT, 2, 66, 23, 102, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_RIGHT + 1, 24, 66, 41, 102, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_RIGHT + 2, 42, 66, 61, 102, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_RIGHT + 3, 62, 66, 83, 102, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_RIGHT + 4, 84, 66, 101, 102, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_RIGHT + 5, 102, 66, 122, 102, tex->Get(TEXTURE_RIGHT_ID));
	ani = new CAnimation(DURATION_ANI_BILL_RUN);
	ani->Add(ID_ANI_BILL_RUN_RIGHT);
	ani->Add(ID_ANI_BILL_RUN_RIGHT + 1);
	ani->Add(ID_ANI_BILL_RUN_RIGHT + 2);
	ani->Add(ID_ANI_BILL_RUN_RIGHT + 3);
	ani->Add(ID_ANI_BILL_RUN_RIGHT + 4);
	ani->Add(ID_ANI_BILL_RUN_RIGHT + 5);

	animation->Add(ID_ANI_BILL_RUN_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_RUN_LEFT, 2, 66, 23, 102, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	sprite->Add(ID_ANI_BILL_RUN_LEFT + 1, 24, 66, 41, 102, tex->Get(TEXTURE_RIGHT_ID),-1.0f);
	sprite->Add(ID_ANI_BILL_RUN_LEFT + 2, 42, 66, 61, 102, tex->Get(TEXTURE_RIGHT_ID),-1.0f);
	sprite->Add(ID_ANI_BILL_RUN_LEFT + 3, 62, 66, 83, 102, tex->Get(TEXTURE_RIGHT_ID),-1.0f);
	sprite->Add(ID_ANI_BILL_RUN_LEFT + 4, 84, 66, 101, 102, tex->Get(TEXTURE_RIGHT_ID),-1.0f);
	sprite->Add(ID_ANI_BILL_RUN_LEFT + 5, 102, 66, 122, 102, tex->Get(TEXTURE_RIGHT_ID),-1.0f);
	ani = new CAnimation(DURATION_ANI_BILL_RUN);
	ani->Add(ID_ANI_BILL_RUN_LEFT);
	ani->Add(ID_ANI_BILL_RUN_LEFT + 1);
	ani->Add(ID_ANI_BILL_RUN_LEFT + 2);
	ani->Add(ID_ANI_BILL_RUN_LEFT + 3);
	ani->Add(ID_ANI_BILL_RUN_LEFT + 4);
	ani->Add(ID_ANI_BILL_RUN_LEFT + 5);

	animation->Add(ID_ANI_BILL_RUN_LEFT, ani);

	//Load run shot animation

	sprite->Add(ID_ANI_BILL_RUN_SHOT_RIGHT, 155, 189, 181, 224, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_SHOT_RIGHT + 1, 184, 189, 208, 224, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_SHOT_RIGHT + 2, 210, 189,  236, 224, tex->Get(TEXTURE_RIGHT_ID));

	ani = new CAnimation(DURATION_ANI_BILL_RUN);
	ani->Add(ID_ANI_BILL_RUN_SHOT_RIGHT);
	ani->Add(ID_ANI_BILL_RUN_SHOT_RIGHT + 1);
	ani->Add(ID_ANI_BILL_RUN_SHOT_RIGHT + 2);

	animation->Add(ID_ANI_BILL_RUN_SHOT_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_RUN_SHOT_LEFT, 155, 189, 181, 224, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	sprite->Add(ID_ANI_BILL_RUN_SHOT_LEFT + 1, 184, 189, 208, 224, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	sprite->Add(ID_ANI_BILL_RUN_SHOT_LEFT + 2, 210, 189, 236, 224, tex->Get(TEXTURE_RIGHT_ID), -1.0f);

	ani = new CAnimation(DURATION_ANI_BILL_RUN);
	ani->Add(ID_ANI_BILL_RUN_SHOT_LEFT);
	ani->Add(ID_ANI_BILL_RUN_SHOT_LEFT + 1);
	ani->Add(ID_ANI_BILL_RUN_SHOT_LEFT + 2);

	animation->Add(ID_ANI_BILL_RUN_SHOT_LEFT, ani);
	//Load run shot up right animation

	sprite->Add(ID_ANI_BILL_RUN_SHOT_UP_RIGHT, 123, 66, 144, 102, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_SHOT_UP_RIGHT + 1, 145, 66, 162, 102, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_SHOT_UP_RIGHT + 2, 163, 66, 183, 102, tex->Get(TEXTURE_RIGHT_ID));

	ani = new CAnimation(DURATION_ANI_BILL_RUN);
	ani->Add(ID_ANI_BILL_RUN_SHOT_UP_RIGHT);
	ani->Add(ID_ANI_BILL_RUN_SHOT_UP_RIGHT + 1);
	ani->Add(ID_ANI_BILL_RUN_SHOT_UP_RIGHT + 2);

	animation->Add(ID_ANI_BILL_RUN_SHOT_UP_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_RUN_SHOT_UP_LEFT, 123, 66, 144, 102, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	sprite->Add(ID_ANI_BILL_RUN_SHOT_UP_LEFT + 1, 145, 66, 162, 102, tex->Get(TEXTURE_RIGHT_ID),-1.0f);
	sprite->Add(ID_ANI_BILL_RUN_SHOT_UP_LEFT + 2, 163, 66, 183, 102, tex->Get(TEXTURE_RIGHT_ID), -1.0f);

	ani = new CAnimation(DURATION_ANI_BILL_RUN);
	ani->Add(ID_ANI_BILL_RUN_SHOT_UP_LEFT);
	ani->Add(ID_ANI_BILL_RUN_SHOT_UP_LEFT + 1);
	ani->Add(ID_ANI_BILL_RUN_SHOT_UP_LEFT + 2);

	animation->Add(ID_ANI_BILL_RUN_SHOT_UP_LEFT, ani);

	//Load run shot down right animation

	sprite->Add(ID_ANI_BILL_RUN_SHOT_DOWN_RIGHT, 184, 66, 206, 102, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_SHOT_DOWN_RIGHT + 1, 207, 66, 228, 102, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_RUN_SHOT_DOWN_RIGHT + 2, 229, 66, 251, 102, tex->Get(TEXTURE_RIGHT_ID));

	ani = new CAnimation(DURATION_ANI_BILL_RUN);
	ani->Add(ID_ANI_BILL_RUN_SHOT_DOWN_RIGHT);
	ani->Add(ID_ANI_BILL_RUN_SHOT_DOWN_RIGHT + 1);
	ani->Add(ID_ANI_BILL_RUN_SHOT_DOWN_RIGHT + 2);

	animation->Add(ID_ANI_BILL_RUN_SHOT_DOWN_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_RUN_SHOT_DOWN_LEFT, 184, 66, 206, 102, tex->Get(TEXTURE_RIGHT_ID),-1.0f);
	sprite->Add(ID_ANI_BILL_RUN_SHOT_DOWN_LEFT + 1, 207, 66, 228, 102, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	sprite->Add(ID_ANI_BILL_RUN_SHOT_DOWN_LEFT + 2, 229, 66, 251, 102, tex->Get(TEXTURE_RIGHT_ID), -1.0f);

	ani = new CAnimation(DURATION_ANI_BILL_RUN);
	ani->Add(ID_ANI_BILL_RUN_SHOT_DOWN_LEFT);
	ani->Add(ID_ANI_BILL_RUN_SHOT_DOWN_LEFT + 1);
	ani->Add(ID_ANI_BILL_RUN_SHOT_DOWN_LEFT + 2);

	animation->Add(ID_ANI_BILL_RUN_SHOT_DOWN_LEFT, ani);
	//Load swim animation
	
	sprite->Add(ID_ANI_BILL_SWIMMING_RIGHT, 130, 115, 147, 131, tex->Get(TEXTURE_RIGHT_ID));

	ani = new CAnimation(DURATION_ANI_BILL_SWIMMING);
	ani->Add(ID_ANI_BILL_SWIMMING_RIGHT);
	
	animation->Add(ID_ANI_BILL_SWIMMING_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_SWIMMING_LEFT, 130, 115, 147, 131, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	
	ani = new CAnimation(DURATION_ANI_BILL_SWIMMING);
	ani->Add(ID_ANI_BILL_SWIMMING_LEFT);

	animation->Add(ID_ANI_BILL_SWIMMING_LEFT, ani);



	//Load jump animation

	sprite->Add(ID_ANI_BILL_JUMP_RIGHT, 117, 44, 134, 65, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_JUMP_RIGHT + 1, 135, 44, 155, 65, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_JUMP_RIGHT + 2, 156, 44, 173, 65, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_JUMP_RIGHT + 3, 174, 44, 194, 65, tex->Get(TEXTURE_RIGHT_ID));

	ani = new CAnimation(DURATION_ANI_BILL_JUMP);

	ani->Add(ID_ANI_BILL_JUMP_RIGHT);
	ani->Add(ID_ANI_BILL_JUMP_RIGHT + 1);
	ani->Add(ID_ANI_BILL_JUMP_RIGHT + 2);
	ani->Add(ID_ANI_BILL_JUMP_RIGHT + 3);

	animation->Add(ID_ANI_BILL_JUMP_RIGHT, ani);
	
	ani = new CAnimation(*ani);
	animation->Add(ID_ANI_BILL_JUMP_LEFT, ani);

	//Load swim start animation

	sprite->Add(ID_ANI_BILL_SWIMMING_START, 94, 115, 111, 131, tex->Get(TEXTURE_RIGHT_ID));
	ani = new CAnimation(175);
	ani->Add(ID_ANI_BILL_SWIMMING_START);
	ani->oneTimeAnimation = true;
	animation->Add(ID_ANI_BILL_SWIMMING_START, ani);

	//Load swimming shot animation

	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_RIGHT, 191, 113, 217, 131, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_RIGHT + 1, 191, 113, 217, 132, tex->Get(TEXTURE_RIGHT_ID));
	ani = new CAnimation(100);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_RIGHT);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_RIGHT + 1);
	animation->Add(ID_ANI_BILL_SWIMMING_SHOT_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_LEFT, 191, 113, 217, 131, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_LEFT + 1, 191, 113, 217, 132, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	ani = new CAnimation(100);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_LEFT);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_LEFT + 1);
	animation->Add(ID_ANI_BILL_SWIMMING_SHOT_LEFT, ani);
	
	//Load swimming shot up animation
	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_RIGHT, 148, 113, 168, 131, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_RIGHT + 1, 148, 113, 168, 132, tex->Get(TEXTURE_RIGHT_ID));
	ani = new CAnimation(100);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_RIGHT);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_RIGHT + 1);
	animation->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_LEFT, 148, 113, 168, 131, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_LEFT + 1, 148, 113, 168, 132, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	ani = new CAnimation(100);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_LEFT);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_LEFT + 1);
	animation->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_LEFT, ani);

	//Load swimming shot up stand animation

	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_RIGHT, 169, 103, 187, 131, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_RIGHT + 1, 169, 103, 187, 132, tex->Get(TEXTURE_RIGHT_ID));
	ani = new CAnimation(100);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_RIGHT);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_RIGHT + 1);
	animation->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_LEFT, 169, 103, 187, 131, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	sprite->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_LEFT + 1, 169, 103, 187, 132, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	ani = new CAnimation(100);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_LEFT);
	ani->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_LEFT + 1);
	animation->Add(ID_ANI_BILL_SWIMMING_SHOT_UP_STAND_LEFT, ani);


	//Load laydown animation
	sprite->Add(ID_ANI_BILL_LAYDOWN_RIGHT, 83, 48, 116, 65, tex->Get(TEXTURE_RIGHT_ID));
	ani = new CAnimation(100);
	ani->Add(ID_ANI_BILL_LAYDOWN_RIGHT);
	animation->Add(ID_ANI_BILL_LAYDOWN_RIGHT, ani);

	sprite->Add(ID_ANI_BILL_LAYDOWN_LEFT, 83, 48, 116, 65, tex->Get(TEXTURE_RIGHT_ID), -1.0f);
	ani = new CAnimation(100);
	ani->Add(ID_ANI_BILL_LAYDOWN_LEFT);
	animation->Add(ID_ANI_BILL_LAYDOWN_LEFT, ani);

	//Load dead animation

	sprite->Add(ID_ANI_BILL_DEAD, 2, 107, 31, 131, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_DEAD + 1, 19, 112, 42, 131, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_DEAD + 2, 43, 107, 59, 131, tex->Get(TEXTURE_RIGHT_ID));
	sprite->Add(ID_ANI_BILL_DEAD + 3, 60, 120, 93, 131, tex->Get(TEXTURE_RIGHT_ID));
	ani = new CAnimation(1000);
	ani->Add(ID_ANI_BILL_DEAD);
	ani->Add(ID_ANI_BILL_DEAD + 1);
	ani->Add(ID_ANI_BILL_DEAD + 2);
	ani->Add(ID_ANI_BILL_DEAD + 3);
	animation->Add(ID_ANI_BILL_DEAD, ani);
}

void CBill::OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (state == BILL_STATE_JUMP || state == BILL_STATE_DEAD)
			SetState(BILL_STATE_IDLE);
		
	}
	if (e->nx != 0 && e->obj->IsBlocking())
		vx = 0;

	if (dynamic_cast<CSoldier*>(e->obj))
		OnCollisionWithSoldier(e);
	if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
}

void CBill::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}


void CBill::OnCollisionWithSoldier(LPCOLLISIONEVENT e)
{
	CSoldier* soldier = dynamic_cast<CSoldier*>(e->obj);

	if (e->nx < 0)
	{
		if (soldier->GetState() != SOLDIER_STATE_DEATH)
		{
			soldier->SetState(SOLDIER_STATE_DEATH);
		}
	}
}
void CBill::OnNoCollision(DWORD dt)
{
	x += dt * vx;
	y += dt * vy;
	vy += Bill_GRAVITY * dt;
	if (y > GROUND_Y)
	{
		vy = 0;
		y = GROUND_Y;
		if (state == BILL_STATE_JUMP) CGame::GetInstance()->ProcessKeyboard();
		if (state == BILL_STATE_JUMP) SetState(BILL_STATE_IDLE);
	}

}

void CBill::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (state == BILL_STATE_IDLE)
	{
		right = x + 24;
		bottom = y - 25;
		return;
	}
	if (state == BILL_STATE_LAYDOWN)
	{
		right = x + 33;
		bottom = y - 17;
		return;
	}
	if (state == BILL_STATE_SWIM || state == BILL_STATE_SWIM_MOVE)
	{
		right = x + 17;
		bottom = y - 17;
		return;
	}
	right = x + 21;
	bottom = y - 25;

}
