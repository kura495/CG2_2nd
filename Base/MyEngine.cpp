#include "MyEngine.h"
#include"Scenes/Manager/GameManager.h"
MyEngine* MyEngine::GetInstance()
{
		static MyEngine instance;
		return &instance;
}

void MyEngine::Initialize(DirectXCommon* directX)
{
	kClientWidth_ = WinApp::kClientWidth;
	kClientHeight_ = WinApp::kClientHeight;
	directX_ = directX;
	
}



