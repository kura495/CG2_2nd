#include"GameManager.h"
void GameManager::Initialize()
{
	//COM�̏�����
	CoInitializeEx(0, COINIT_MULTITHREADED);
	//�E�B���h�E�N���X
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