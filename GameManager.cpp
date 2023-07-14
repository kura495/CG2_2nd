#include"GameManager.h"
void GameManager::Initialize()
{
	//COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);
	//Window
	winApp = new WinApp();
	kClientWidth = 1280;
	kClientHeight = 720;
	winApp->Initialize(kClientWidth, kClientHeight);
	//DirectX
	directX = new DirectXCommon();
	directX->Initialize(winApp, kClientWidth, kClientHeight);
	//Engine
	myEngine = new MyEngine();
	myEngine->Initialize(directX, kClientWidth, kClientHeight);
	//ImGui
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(winApp, directX);
	//State
	//state = new GameTitleState();
}
void GameManager::Gameloop()
{
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			imGuiManager->BeginFrame();
			directX->PreView();
			//state->Update();
			//state->Draw();
			imGuiManager->EndFrame();
			directX->PostView();
		}
	}
	Release();
}

void GameManager::Release()
{
	ImGui_ImplDX12_Shutdown();
	delete myEngine;
	delete directX;
	CoUninitialize();
	IDXGIDebug1* debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		debug->Release();
	}
}
