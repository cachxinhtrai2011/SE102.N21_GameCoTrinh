#include "BillInputHandler.h"
#include "Bill.h"
#include "Bullet.h"
#include "NormalGun.h"
#include "CircularGun.h"
#include "SpreadGun.h"
#include "FireGun.h"
#include "RifleGun.h"
#include "LAirCraft.h"
extern CBill* bill;
CBillInputHandler::CBillInputHandler(): CInputHandler()
{
	KeyToListen.push_back(DIK_LEFTARROW); 
	KeyToListen.push_back(DIK_RIGHTARROW); 
	KeyToListen.push_back(DIK_S);
	KeyToListen.push_back(DIK_0); 
	KeyToListen.push_back(DIK_1);
	KeyToListen.push_back(DIK_2);
	KeyToListen.push_back(DIK_3);
	KeyToListen.push_back(DIK_5);
	KeyToListen.push_back(DIK_A);
	KeyToListen.push_back(DIK_K);
}
void CBillInputHandler::HandleInput(CInput* input)
{
	if (bill->GetState() == BILL_STATE_DEAD)
		return;
	switch (input->GetType())
	{
	case KEY_CLICK:
		onKeyClick(input->GetInput());
		break;
	case KEY_DOWN:
		onKeyPress(input->GetInput());
		break;
	case KEY_UP:
		onKeyRelease(input->GetInput());
		break;
	default:
		break;
	}
}

void CBillInputHandler::onKeyClick(int keyCode)
{
	if (keyCode == DIK_RIGHTARROW)
	{
		bill->SetFaceDirection(1);
		if(bill->GetState() != BILL_STATE_LAYDOWN)
			bill->SetSpeedX(BILL_RUN_SPEED);
		if (bill->GetState() == BILL_STATE_JUMP)
			return;
		if(bill->GetState() != BILL_STATE_LAYDOWN)
			if (bill->GetState() == BILL_STATE_SWIM || bill->GetState() == BILL_STATE_SWIM_MOVE)
				bill->SetState(BILL_STATE_SWIM_MOVE);
			else
				bill->SetState(BILL_STATE_RUN);
		return;
	}
	if (keyCode == DIK_LEFTARROW)
	{
		bill->SetFaceDirection(-1);
		if(bill->GetState() != BILL_STATE_LAYDOWN)
			bill->SetSpeedX(-BILL_RUN_SPEED);
		if (bill->GetState() == BILL_STATE_JUMP)
			return;
		if (bill->GetState() != BILL_STATE_LAYDOWN)
			if (bill->GetState() == BILL_STATE_SWIM || bill->GetState() == BILL_STATE_SWIM_MOVE)
				bill->SetState(BILL_STATE_SWIM_MOVE);
			else
				bill->SetState(BILL_STATE_RUN);
		return;
	}
	if (keyCode == DIK_S && bill->GetState() == BILL_STATE_LAYDOWN)
	{
		bill->setIsOnGround(0);
		bill->SetPosition(bill->GetX(), bill->GetY() - 1.0f);
		CAnimations::GetInstance()->Get(ID_ANI_BILL_IDLE_LEFT)->SetStartAnimation(CAnimations::GetInstance()->Get(ID_ANI_BILL_SWIMMING_START));
		bill->SetState(BILL_STATE_IDLE);
		return;
	}

	if (keyCode == DIK_S && bill->GetState() != BILL_STATE_JUMP && bill->IsOnGround() == 1)
	{
		bill->setIsOnGround(0);
		bill->SetState(BILL_STATE_JUMP);
		return;
	}

	if (keyCode == DIK_0)
	{
		bill->SetGun(new CNormalGun());
		return;
	}
	if (keyCode == DIK_1)
	{
		bill->SetGun(new CCircularGun());
		return;
	}
	if (keyCode == DIK_2)
	{
		bill->SetGun(new CSpreadGun());
		return;
	}
	if (keyCode == DIK_3)
	{
		bill->SetGun(new CFireGun());
		return;
	}
	if (keyCode == DIK_5)
	{
		bill->SetGun(new CRifleGun());
		return;
	}
	if (keyCode == DIK_A)
	{
		bill->isShotting = true;
		return;
	}
	if (keyCode == DIK_J) {
		//CGame::GetInstance()->GetDirect3DDevice()->RSGetViewports()->
	}
}

void CBillInputHandler::onKeyPress(int keyCode)
{
	if (keyCode == DIK_UPARROW)
		bill->shotDirection = 1;
	if (keyCode == DIK_DOWNARROW)
		bill->shotDirection = -1;
	if (keyCode == DIK_X)
	{
		if(bill->faceDirection == 1)
			CAnimations::GetInstance()->Get(ID_ANI_BILL_SWIMMING_RIGHT)->SetStartAnimation(CAnimations::GetInstance()->Get(ID_ANI_BILL_SWIMMING_START));
		else
			CAnimations::GetInstance()->Get(ID_ANI_BILL_SWIMMING_LEFT)->SetStartAnimation(CAnimations::GetInstance()->Get(ID_ANI_BILL_SWIMMING_START));
		bill->SetState(BILL_STATE_SWIM);
		return;
	}
	if (keyCode == DIK_Z)
		bill->SetState(BILL_STATE_LAYDOWN);
	if (keyCode == DIK_4)
	{
		CGame::GetInstance()->gameObjects.push_back(new CLAirCraft(bill->GetX(), 0));
	}
	if (keyCode == DIK_K) {
		CGame::GetInstance()->InitiateSwitchScene(CGame::GetInstance()->GetCurrentSceneID() + 1);
		CGame::GetInstance()->SwitchScene();
		return;
	}
}

void CBillInputHandler::onKeyRelease(int keyCode)
{
	if (bill->GetState() != BILL_STATE_JUMP)
	{
		if (keyCode == DIK_RIGHTARROW || keyCode == DIK_LEFTARROW)
		{
			bill->SetSpeedX(0.0f);
			if (bill->GetState() == BILL_STATE_RUN)
				bill->SetState(BILL_STATE_IDLE);
		}
	}
	if (keyCode == DIK_A)
		bill->isShotting = false;
	if (keyCode == DIK_UPARROW)
		bill->shotDirection = 0;
	if (keyCode == DIK_DOWNARROW)
		bill->shotDirection = 0;
	if (keyCode == DIK_Z)
	{
		bill->SetPosition(bill->GetX(), bill->GetY() + 20.0f);
		bill->SetState(BILL_STATE_IDLE);
	}
}