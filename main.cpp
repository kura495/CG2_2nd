#include"Bace\WinApp.h"
#include"Bace\DirectXCommon.h"
#include"Bace\MyEngine.h"
#include"Scene\GameScene.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	

	MSG msg{};

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
