#include"WinApp.h"
#include"DirectXCommon.h"
#include"Mesh.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ウィンドウクラス
	WinApp* winApp = new WinApp();
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	winApp->Initialize(kClientWidth, kClientHeight);
	//DirectX
	DirectXCommon* directX = new DirectXCommon();
	directX->Initialize(winApp, kClientWidth, kClientHeight);
	Vector4 Left[10] = {
		{-0.1f,0.9f,0.0f,1.0f},
		{-0.1f,0.8f,0.0f,1.0f},
		{-0.1f,0.7f,0.0f,1.0f},
		{-0.1f,0.6f,0.0f,1.0f},
		{-0.1f,0.5f,0.0f,1.0f},
		{-0.1f,0.4f,0.0f,1.0f},
		{-0.1f,0.3f,0.0f,1.0f},
		{-0.1f,0.2f,0.0f,1.0f},
		{-0.1f,0.1f,0.0f,1.0f},
		{-0.1f,0.0f,0.0f,1.0f}
	};
	Vector4 Top[10] = {
		{0.0f,1.0f,0.0f,1.0f},
		{0.0f,0.9f,0.0f,1.0f},
		{0.0f,0.8f,0.0f,1.0f},
		{0.0f,0.7f,0.0f,1.0f},
		{0.0f,0.6f,0.0f,1.0f},
		{0.0f,0.5f,0.0f,1.0f},
		{0.0f,0.4f,0.0f,1.0f},
		{0.0f,0.3f,0.0f,1.0f},
		{0.0f,0.2f,0.0f,1.0f},
		{0.0f,0.1f,0.0f,1.0f}
	};
	Vector4 Right[10] = {
		{0.1f,0.9f,0.0f,1.0f},
		{0.1f,0.8f,0.0f,1.0f},
		{0.1f,0.7f,0.0f,1.0f},
		{0.1f,0.6f,0.0f,1.0f},
		{0.1f,0.5f,0.0f,1.0f},
		{0.1f,0.4f,0.0f,1.0f},
		{0.1f,0.3f,0.0f,1.0f},
		{0.1f,0.2f,0.0f,1.0f},
		{0.1f,0.1f,0.0f,1.0f},
		{0.1f,0.0f,0.0f,1.0f},
	};
	Mesh* mesh[10];
	for (int i = 0; i < 10; i++) {
		mesh[i] = new Mesh();
		mesh[i]->Initialize(directX,Left[i], Top[i], Right[i]);
	}
	MSG msg{};

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//ゲームループ
			directX->PreView();
			for (int i = 0; i < 10; i++) {
				mesh[i]->Draw();
			}
			directX->PostView();
		}
	}
	for (int i = 0; i < 10; i++) {
		mesh[i]->Release();
	}
	directX->Release();
}