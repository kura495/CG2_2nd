#pragma once
#include"WinApp.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"Mesh.h"
#include"TextureManager.h"
#include"Light.h"
#include"ImGuiManager.h"
#include"Scenes/State/GameTitleState.h"
#include"Scenes/State/GamePlayState.h"
#include"Scenes/State/GameClearState.h"
#include"Scenes/State/IgameState.h"
#include"Audio.h"
#include"Input.h"
#include"GlobalVariables.h"

class GameManager
{
public:
	void Run();
	
	
private:
	void Initialize();
	void Gameloop();
	//Base
	enum GameStateNo {
		TITLE,
		PLAY,
		GameStateMax
	};
	WinApp* winApp = nullptr;
	DirectXCommon* directX = nullptr;
	MyEngine* myEngine = nullptr;
	//ウィンドウサイズ
	int32_t kClientWidth;
	int32_t kClientHeight;
	ImGuiManager* imGuiManager = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	TextureManager* textureManager = nullptr;
	Light* light = nullptr;

	MSG msg{};
	//State
	std::unique_ptr<GameState>state[GameStateMax];
	Vector4 ClearColor{ 0.1f,0.25f,0.5f,1.0f };

	void Release();
};


