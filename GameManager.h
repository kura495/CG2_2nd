#pragma once
#include"Base/WinApp.h"
#include"Base/DirectXCommon.h"
#include"Base/MyEngine.h"
#include"Utility/ImGuiManager.h"
#include"Scene/State/GameTitleState.h"
#include"Scene/State/GamePlayState.h"
#include"Scene/State/GameClearState.h"
#include"Scene/State/IgameState.h"
class GameManager
{
public:
	
	void Initialize();
	void Gameloop();
	
private:
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
	
	MSG msg{};
	//State
	std::unique_ptr<GameState>state[GameStateMax];


	void Release();
};


