#include"GameManager.h"
void GameManager::Run()
{
	Initialize();
	Gameloop();
	Release();
}
void GameManager::Initialize()
{
	//COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);
	//Window
	winApp = new WinApp();
	winApp->Initialize();
	//DirectX
	directX = DirectXCommon::GetInstance();
	directX->Initialize(winApp);
	//Engine
	myEngine = MyEngine::GetInstance();
	myEngine->Initialize(directX, kClientWidth, kClientHeight);
	//Audio
	Audio = XAudio2::GetInstance();
	Audio->Initialize();
	//Input
	input = Input::GetInstance();
	input->Initialize(winApp);
	//ImGui
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(winApp, directX);
	//TextureManager
	textureManager = TextureManager::GetInstance();
	textureManager->Initialize(directX);
	//Light
	light = Light::GetInstance();
	light->Initialize();
	postprosess = new Postprosess();
	postprosess->Initialize(WinApp::kClientWidth, WinApp::kClientHeight, directX);

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
			input->Update();
			state[GameState::StateNo]->Update();
			state[GameState::StateNo]->Draw();
			imGuiManager->EndFrame();
			directX->PostView();
		}
	}
	
}

void GameManager::Release()
{
	ImGui_ImplDX12_Shutdown();
	CoUninitialize();
	//delete this;
}
