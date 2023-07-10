#include"GameScene.h"

void GameScene::Initialize(DirectXCommon* directX, MyEngine* myEngine,WinApp*winApp,int32_t kClientWidth,int32_t kClientHeight)
{
	directX_ = directX;
	myEngine_ = myEngine;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;
	camera_ = new Camera();
	camera_->Initialize(kClientWidth_, kClientHeight_);
	ImGuiManager_ = new ImGuiManager();
	ImGuiManager_->Initialize(winApp,directX_);
	//リソースを作る
	UV=myEngine_->LoadTexture("resources/uvChecker.png");
	Ball=myEngine_->LoadTexture("resources/monsterBall.png");
}

void GameScene::UpDate()
{
	camera_->Update();
	
}

void GameScene::Draw()
{
	
	ImGuiManager_->BeginFrame();
	directX_->PreView();
	//描画ここから
#pragma region ImGui
	ImGui::Begin("Color");
	float ImGuiColor[Vector3D] = { Color[0].x,Color[0].y ,Color[0].z };
	ImGui::SliderFloat3("RGB", ImGuiColor, 0, 1, "%.3f");
	Color[0] = { ImGuiColor[x],ImGuiColor[y],ImGuiColor[z] };
	ImGui::End();
	camera_->ImGui();
	myEngine_->ImGui();
	ImGui::Begin("Sphere");
	ImGui::Checkbox("Texture",&useMonsterBall);
	ImGui::End();
	if (useMonsterBall == true) {
		SphereTexture = Ball;
	}
	else {
		SphereTexture = UV;
	}
#pragma endregion
	
	myEngine_->Draw(Left[0], Top[0], Right[0], Color[0], camera_->transformationMatrixData, UV);
	//myEngine_->DrawSprite(LeftTop, LeftBottom, RightTop, RightBottom, UV);
	myEngine_->DrawSphere(sphere, camera_->transformationMatrixData, SphereTexture);
	//描画ここまで
	ImGuiManager_->EndFrame();
	directX_->PostView();
}

void GameScene::Release()
{
	ImGui_ImplDX12_Shutdown();
	myEngine_->Release();
	directX_->Release();
}
