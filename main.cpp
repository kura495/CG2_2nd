#include"WinApp.h"
#include"DirectXCommon.h"
#include"Mesh.h"
#include"Scene\GameScene.h"
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
	Mesh* mesh_ = new Mesh();
	mesh_->Initialize(directX, kClientWidth, kClientHeight);

	MSG msg{};
	GameScene* gameScene = new GameScene();
	gameScene->Initialize(directX, mesh_,winApp, kClientWidth, kClientHeight);

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			gameScene->UpDate();
			gameScene->Draw();
		}
	}
	gameScene->Release();
	CoUninitialize();
	IDXGIDebug1* debug;
if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
	debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
	debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
	debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
	debug->Release();
}
}
