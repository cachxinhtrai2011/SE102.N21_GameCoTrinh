#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <dinput.h>
#define DIRECTINPUT_VERSION 0x0800

#include "GameObject.h"
#include "Texture.h"
#include "Scene.h"
#include "PlayScreen.h"
#define SCREEN_WIDTH 272
#define SCREEN_HEIGHT 256
#define MAX_FRAME_RATE 120
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

/*
	Our simple game framework
*/
class CGame
{
	int screen_height;
	int screen_width;

	LPCINPUT keyHandler;

	static CGame* __instance;
	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state
	
	LPD3DX10SPRITE spriteObject;						// Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????
	
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	HINSTANCE hInstance;
	unordered_map<int, LPSCENE> scenes;
	int current_scene = -1;
	int next_scene = 0;

public:

	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void _ParseSection_FONTS(string line);
	void Load(LPCWSTR gameFile);
	void LoadDemo();
	void InitiateSwitchScene(int scene_id);
	void SwitchScene();
	int GetCurrentSceneID() { return current_scene; }

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);
	void _ParseSection_TEXTURES(string line);


	float GetCamX() { return cam_x; }
	float GetCamY() { return cam_y; }
	vector<LPGAMEOBJECT> gameObjects;
	// Init DirectX, Sprite Handler
	void Init(HINSTANCE hInstance);
	//Create game Window
	HWND CreateGameWindow(int ScreenWidth, int ScreenHeight);
	//
	// Draw a portion or ALL the texture at position (x,y) on the screen
	// rect : if NULL, the whole texture will be drawn
	//        if NOT NULL, only draw that portion of the texture 
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b)
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		D3DXVECTOR2 Pos = setWorldToSceen(D3DXVECTOR2(x, y));
		
		this->Draw(x, y, tex, &rect);
	}

	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	// Keyboard related functions 
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }

	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; }

	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }
	static CGame* GetInstance();
	HWND GetHWnd() { return hWnd; }

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }

	void World2Cam(float& x, float& y);
	void Cam2World(float& x, float& y);

	D3DXVECTOR2 setWorldToSceen(D3DXVECTOR2);

	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }
	bool IsSceneChange() { return (current_scene != next_scene); }
	~CGame();
};