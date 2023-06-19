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
	myEngine_->LoadTexture("resources/uvChecker.png");
}

void GameScene::UpDate()
{
	camera_->Update();
}

void GameScene::Draw()
{
	
	ImGuiManager_->BeginFrame();
	directX_->PreView();
	//ここから
#pragma region ImGui
	ImGui::Begin("TriAngleColor");
	float ImGuiColor[Vector3D] = { Color[0].x,Color[0].y ,Color[0].z };
	ImGui::SliderFloat3("RGB", ImGuiColor, 0, 1, "%.3f");
	Color[0] = { ImGuiColor[x],ImGuiColor[y],ImGuiColor[z] };
	ImGui::End();
	camera_->ImGui();
	myEngine_->ImGui();
	ImGui::Begin("SpriteRect");

	float ImGuiSpriteLeftTop[Vector3D] = { LeftTop.x,LeftTop.y ,LeftTop.z };
	ImGui::SliderFloat3("LeftTop", ImGuiSpriteLeftTop,-1.0f, 1.0f,"%.3f");
	LeftTop = { ImGuiSpriteLeftTop[x],ImGuiSpriteLeftTop[y],ImGuiSpriteLeftTop[z] };

	float ImGuiSpriteLeftBottom[Vector3D] = { LeftBottom.x,LeftBottom.y ,LeftBottom.z };
	ImGui::SliderFloat3("LeftBottom", ImGuiSpriteLeftBottom,-1.0f, 1.0f,"%.3f");
	LeftBottom = { ImGuiSpriteLeftBottom[x],ImGuiSpriteLeftBottom[y],ImGuiSpriteLeftBottom[z] };

	float ImGuiSpriteRightTop[Vector3D] = { RightTop.x,RightTop.y ,RightTop.z };
	ImGui::SliderFloat3("RightTop", ImGuiSpriteRightTop, -1.0f, 1.0f, "%.3f");
	RightTop = { ImGuiSpriteRightTop[x],ImGuiSpriteRightTop[y],ImGuiSpriteRightTop[z] };

	float ImGuiSpriteRightBottom[Vector3D] = { RightBottom.x,RightBottom.y ,RightBottom.z };
	ImGui::SliderFloat3("RightBottom", ImGuiSpriteRightBottom, -1.0f, 1.0f, "%.3f");
	RightBottom = { ImGuiSpriteRightBottom[x],ImGuiSpriteRightBottom[y],ImGuiSpriteRightBottom[z] };
	ImGui::End();
#pragma endregion
	
	myEngine_->Draw(Left[0], Top[0], Right[0], Color[0], camera_->transformationMatrixData);
	myEngine_->DrawSprite(LeftTop, LeftBottom, RightTop, RightBottom);
	//ここまで
	ImGuiManager_->EndFrame();
	directX_->PostView();
}

void GameScene::Release()
{
	ImGui_ImplDX12_Shutdown();
	myEngine_->Release();
	directX_->Release();
}
