#include"WinApp.h"
#include"DirectX.h"
#include"DrawEngine.h"
#define RED Vector4{ 1.0f,0.0f,0.0f,1.0f };
#define GREEN Vector4{ 0.0f,1.0f,0.0f,1.0f };
#define BLUE Vector4{ 0.0f,0.0f,1.0f,1.0f };
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ウィンドウクラス
	WinApp* winApp = new WinApp();
	int32_t kClientWidth = 1280;
	int32_t kClientHeight = 720;

	

	winApp->Initialize(kClientWidth, kClientHeight);
	//DirectX
	DirectX* directX = new DirectX();
	directX->Initialize(winApp, kClientWidth, kClientHeight);
	DrawEngine* drawEngine[10];
	for (int i = 0; i < 10; i++) {
		drawEngine[i] = new DrawEngine();
		drawEngine[i]->Initialize(directX);
	}
	MSG msg{};
	const int kTriangleMax = 10;
	Vector4 Left[kTriangleMax] = {
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
	Vector4 Top[kTriangleMax] = {
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
	Vector4 Right[kTriangleMax] = {
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
	Vector4 Color[kTriangleMax] = {
		{ 1.0f,0.0f,0.0f,1.0f },//RED
		{ 0.0f,1.0f,0.0f,1.0f },//GREEN
		{ 0.0f,0.0f,1.0f,1.0f },//BLUE
		{ 1.0f,0.0f,0.0f,1.0f },
		{ 0.0f,1.0f,0.0f,1.0f },
		{ 0.0f,0.0f,1.0f,1.0f },
		{ 1.0f,0.0f,0.0f,1.0f },
		{ 0.0f,1.0f,0.0f,1.0f },
		{ 0.0f,0.0f,1.0f,1.0f },
		{ 1.0f,0.0f,0.0f,1.0f },
	};
	Transform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			transform.rotate.y += 0.03f;
			//ゲームループ
			directX->PreView();
			for (int i = 0; i < kTriangleMax; i++) {
				drawEngine[i]->Draw(Left[i], Top[i], Right[i], Color[i], transform);
			}
			directX->PostView();
		}
	}
	for (int i = 0; i < kTriangleMax; i++) {
		drawEngine[i]->Release();
	}
	
	directX->Release();
}