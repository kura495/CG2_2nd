#include"GameScene.h"

void GameScene::Initialize(DirectXCommon* directX, MyEngine* myEngine,WinApp*winApp,int32_t kClientWidth,int32_t kClientHeight)
{
	directX_ = directX;
	myEngine_ = myEngine;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;
}

void GameScene::UpDate()
{

}

void GameScene::Draw()
{
	directX_->PreView();
	//ここから
	myEngine_->Draw(Left,Top,Right,Color,transform);
	//ここまで
	directX_->PostView();
}

void GameScene::Release()
{
	myEngine_->Release();
	directX_->Release();
}
