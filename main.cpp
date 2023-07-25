#include"Base/WinApp.h"
#include"Base/DirectXCommon.h"
#include"Base/MyEngine.h"
#include"GameScene.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);
	//ウィンドウクラス
	WinApp* winApp = new WinApp();
	int32_t kClientWidth = 1280;
	int32_t kClientHeight = 720;

	winApp->Initialize(kClientWidth, kClientHeight);
	//DirectX
	DirectXCommon* directX = new DirectXCommon();
	directX->Initialize(winApp, kClientWidth, kClientHeight);
	MyEngine* myEngine = new MyEngine();
	myEngine->Initialize(directX, kClientWidth, kClientHeight);

	MSG msg{};
	GameScene* gameScene = new GameScene();
	gameScene->Initialize(directX,myEngine,winApp, kClientWidth, kClientHeight);

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//ゲームループ
			/*directX->PreView();
			for (int i = 0; i < kTriangleMax; i++) {
				drawEngine[i]->Draw(Left[i], Top[i], Right[i], Color[i], transform);
			}
			directX->PostView();*/
			gameScene->UpDate();
			gameScene->Draw();
		}
	}
	/*for (int i = 0; i < kTriangleMax; i++) {
		drawEngine[i]->Release();
	}*/
	gameScene->Release();
	CoUninitialize();
}