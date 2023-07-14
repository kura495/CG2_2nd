#pragma once
#include"Bace/WinApp.h"
#include"Bace/DirectXCommon.h"
#include"Bace/MyEngine.h"
#include"Utility/ImGuiManager.h"
#include"Scene/State/GameTitleState.h"
#include"Scene/State/GamePlayState.h"
#include"Scene/State/GameClearState.h"
class GameManager
{
public:

	void Initialize();
	void Gameloop();
	
private:
	//Base
	WinApp* winApp = nullptr;
	DirectXCommon* directX = nullptr;
	MyEngine* myEngine = nullptr;
	//ウィンドウサイズ
	int32_t kClientWidth;
	int32_t kClientHeight;
	ImGuiManager* imGuiManager = nullptr;

	MSG msg{};
	//State
	GameState* state=nullptr;

	void Release();
};


