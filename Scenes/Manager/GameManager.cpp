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
	myEngine =MyEngine::GetInstance();
	myEngine->Initialize(directX, kClientWidth, kClientHeight);

	input = Input::GetInstance();
	input->Initialize(winApp);
	//ImGui
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(winApp, directX);
	//State
	state[TITLE]=std::make_unique<GameTitleState>();
	state[PLAY]= std::make_unique<GamePlayState>();
	state[PLAY]->Initialize();
	GameState::StateNo = TITLE;

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
			state[GameState::StateNo]->Update();
			state[GameState::StateNo]->Draw();
			imGuiManager->EndFrame();
			directX->PostView();
		}
	}
	Release();
}

void GameManager::Release()
{
	ImGui_ImplDX12_Shutdown();
	CoUninitialize();
	
}
