#pragma once
#include"Base/WinApp.h"
#include"Base/DirectXCommon.h"
#include"Base/MyEngine.h"
#include"Utility/ImGuiManager.h"
#include"Scenes/State/GameTitleState.h"
#include"Scenes/State/GamePlayState.h"
#include"Scenes/State/GameClearState.h"
#include"Scenes/State/IgameState.h"
#include"Audio/XAudio2.h"
#include"Input/Input.h"
#include"Base/Mesh.h"
#include"Base/TextureManager.h"
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
	XAudio2* Audio = nullptr;
	TextureManager* textureManager = nullptr;

	MSG msg{};
	//State
	std::unique_ptr<GameState>state[GameStateMax];


	void Release();
};


