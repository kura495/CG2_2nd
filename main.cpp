#include"WinApp.h"
#include"DirectXCommon.h"
#include"Mesh.h"
#include"Scene.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ウィンドウクラス
	WinApp* winApp = new WinApp();
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	winApp->Initialize(kClientWidth, kClientHeight);
	//DirectX
	DirectXCommon* directX = new DirectXCommon();
	directX->Initialize(winApp, kClientWidth, kClientHeight);
	Scene* scene = new Scene();
	scene->Initialize(directX);
	MSG msg{};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//ゲームループ
			directX->PreView();
			scene->Draw();
			directX->PostView();
		}
	}
	scene->Release();
	directX->Release();
}