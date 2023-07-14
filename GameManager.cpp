#include"GameManager.h"
void GameManager::Initialize()
{
	//COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);
	//ウィンドウクラス
	winApp = new WinApp();
	kClientWidth = 1280;
	kClientHeight = 720;

	winApp->Initialize(kClientWidth, kClientHeight);
	//DirectX
	directX = new DirectXCommon();
	directX->Initialize(winApp, kClientWidth, kClientHeight);
	myEngine = new MyEngine();
	myEngine->Initialize(directX, kClientWidth, kClientHeight);
	state = new GameTitle();
	gameScene = new GameScene();
	gameScene->Initialize(directX, myEngine, winApp, kClientWidth, kClientHeight);

}