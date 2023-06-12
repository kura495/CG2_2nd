#include"GameScene.h"

void GameScene::Initialize(DirectXCommon* directX, MyEngine* myEngine,WinApp*winApp,int32_t kClientWidth,int32_t kClientHeight)
{

	directX_ = directX;
	myEngine_ = myEngine;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;
	camera_ = new Camera();
	camera_->Initialize(kClientWidth_, kClientHeight_);
}

void GameScene::UpDate()
{
	camera_->Update();
	transform.rotate.y += 0.03f;
}

void GameScene::Draw()
{
	directX_->PreView();
	//ここから
	myEngine_->Draw(Left,Top,Right,Color,transform,camera_->transformationMatrixData);
	//ここまで
	directX_->PostView();
}

void GameScene::Release()
{
	myEngine_->Release();
	directX_->Release();
}
