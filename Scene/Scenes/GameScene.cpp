#include"GameScene.h"
void GameScene::Initialize(MyEngine* myEngine)
{
	MyEngine* myEngine_ = myEngine;
	camera_ = new Camera();
	camera_->Initialize(1280, 720);

	//リソースを作る
	UV=myEngine_->LoadTexture("resources/uvChecker.png");
	Ball=myEngine_->LoadTexture("resources/monsterBall.png");
	modelData= myEngine_->LoadObjFile("resources","Plane.obj");
}

void GameScene::UpDate()
{
	camera_->Update();
}

void GameScene::Draw()
{
	
	
	//描画ここから
#pragma region ImGui
	ImGui::Begin("Color");
	float ImGuiColor[Vector3D] = { Color[0].x,Color[0].y ,Color[0].z };
	ImGui::SliderFloat3("RGB", ImGuiColor, 0, 1, "%.3f");
	Color[0] = { ImGuiColor[x],ImGuiColor[y],ImGuiColor[z] };
	ImGui::End();
	camera_->ImGui();
	ImGui::Begin("Sphere");
	ImGui::Checkbox("Texture",&useMonsterBall);
	ImGui::End();
	if (useMonsterBall == true) {
		SphereTexture = Ball;
	}
	else {
		SphereTexture = UV;
	}
	ImGui::Begin("Box");
	float ImGuiScale[Vector3D] = { Box.scale.x,Box.scale.y ,Box.scale.z };
	ImGui::SliderFloat3("Scale", ImGuiScale, 1, 30, "%.3f");
	Box.scale = { ImGuiScale[x],ImGuiScale[y],ImGuiScale[z] };
	float ImGuiRotate[Vector3D] = { Box.rotate.x,Box.rotate.y ,Box.rotate.z };
	ImGui::SliderFloat3("Rotate", ImGuiRotate, -5, 5, "%.3f");
	Box.rotate = { ImGuiRotate[x],ImGuiRotate[y],ImGuiRotate[z] };
	float ImGuiTranslate[Vector3D] = { Box.translate.x,Box.translate.y ,Box.translate.z };
	ImGui::SliderFloat3("Translate", ImGuiTranslate, -10, 10, "%.3f");
	Box.translate = { ImGuiTranslate[x],ImGuiTranslate[y],ImGuiTranslate[z] };
	ImGui::End();
#pragma endregion
	
	//myEngine_->Draw(Left[0], Top[0], Right[0], Color[0], camera_->transformationMatrixData, UV);
	//myEngine_->Draw(Left[1], Top[1], Right[1], Color[0], camera_->transformationMatrixData, UV);
	//myEngine_->DrawSprite(LeftTop[0], LeftBottom[0], RightTop[0], RightBottom[0], Color[0], UV);
	//myEngine_->DrawSphere(sphere, camera_->transformationMatrixData,Color[0], SphereTexture);
	//myEngine_->DrawModel(modelData,{0,0,0}, camera_->transformationMatrixData,Color[0]);
	//描画ここまで
	//myEngine->VertexReset();
	
}
