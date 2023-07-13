#pragma once
#include"Bace\MyEngine.h"
#include"Scene\GameScene.h"
#include"GameObject\Camera\Camera.h"
#include"Utility\ImGuiManager.h"
class GameManager
{
public:
	GameManager();
	~GameManager();

	void Initialize();

	

private:
	//Base
	WinApp* winApp = nullptr;
	DirectXCommon* directX = nullptr;
	MyEngine* myEngine = nullptr;
	//ウィンドウサイズ
	int32_t kClientWidth;
	int32_t kClientHeight;
	//Scenes
	GameScene* gameScene = nullptr;

};


