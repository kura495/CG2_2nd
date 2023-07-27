#include "MyEngine.h"
#include"Scenes/Manager/GameManager.h"
MyEngine* MyEngine::GetInstance()
{
		static MyEngine instance;
		return &instance;
}

void MyEngine::Initialize(DirectXCommon* directX, int32_t kClientWidth, int32_t kClientHeight)
{
	kClientWidth_ = WinApp::kClientWidth;
	kClientHeight_ = WinApp::kClientHeight;
	directX_ = directX;

	
}



