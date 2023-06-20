#include <d3d10.h>
#include <D3DX10.h>
#include <Windows.h>
#include "Game.h"
#include <msxml.h>
#include <MsXml6.h>
#include <iostream>
#include "Textures.h"
#include "Sprites.h"
#include "Animations.h"
#include "Bill.h"
#include "Grass.h"
#include <vector>
#define TEXTURE_PATH L"./Resources/Images/bill_animation.png"
#define BACKGROUND_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)
#define SCREEN_WIDTH 255
#define SCREEN_HEIGHT 255

CTextures* tex;
CAnimations* animation;
CSprites* sprite;
CBill* bill = NULL;
CBullet* bullet;
int done = 0;
void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);


		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);
		//for (int i = 0; i < g->gameObjects.size(); i++)
		//	g->gameObjects[i]->Render();
		CGame::GetInstance()->GetCurrentScene()->Render();

		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	CGame::GetInstance()->GetCurrentScene()->Update(dt);
}

/*
	Render a frame 
*/

void Run()
{
	//int done = 0;
	//while (!done)
	//{
	//	CGame::GetInstance()->ProcessKeyboard();
	//	CGame* game = CGame::GetInstance();
	//	//for (int i = 0; i < game->gameObjects.size(); i++)
	//	//	game->gameObjects[i]->Update(10, &(game->gameObjects));
	//	CGame::GetInstance()->GetCurrentScene()->Update(dt);

	//	Render();
	//	CGame::GetInstance()->SwitchScene();

	//	Sleep(10);
	//}
	MSG msg;
	ULONGLONG frameStart = GetTickCount64();
	DWORD tickPerFrame = 3600 / MAX_FRAME_RATE;

	
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = (DWORD)(now - frameStart);
		if (dt >= tickPerFrame)
		{
			if (CGame::GetInstance()->IsSceneChange())
				CGame::GetInstance()->SwitchScene();
			frameStart = now;
			CGame::GetInstance()->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CGame* game = CGame::GetInstance();
	game->CreateGameWindow(SCREEN_WIDTH,SCREEN_HEIGHT);
	game->Init(hInstance);
	game->InitKeyboard();
	game->Load(L"./Resources/Map/demo.txt");
	bill = (CBill*)game->GetCurrentScene()->GetPlayer();
	
	//game->InitKeyboard();
	SetWindowPos(game->GetHWnd(), 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	//SetWindowPos(game->GetHWnd(), 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	Run(); 
	return 0;
}
