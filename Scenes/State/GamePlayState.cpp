#include"Scenes/State/GamePlayState.h"

//GamePlayState::GamePlayState()
//{
//	camera_ = new Camera();
//	camera_->Initialize(1280, 720);
//	myEngine = MyEngine::GetInstance();
//	//リソースを作る
//	UV = myEngine->LoadTexture("resources/uvChecker.png");
//	Ball = myEngine->LoadTexture("resources/monsterBall.png");
//	modelData = myEngine->LoadObjFile("resources", "Plane.obj");
//}

void GamePlayState::Initialize()
{
	camera_ = new Camera();
	camera_->Initialize(1280, 720);
	myEngine = MyEngine::GetInstance();
	//リソースを作る
	UV = myEngine->LoadTexture("resources/uvChecker.png");
	Ball = myEngine->LoadTexture("resources/monsterBall.png");
	modelData = myEngine->LoadObjFile("resources", "Plane.obj");
}

void GamePlayState::Update()
{
	camera_->Update();
	
}

void GamePlayState::Draw()
{
	myEngine->Draw(Left[0], Top[0], Right[0], Color[0], camera_->transformationMatrixData, UV);
	myEngine->Draw(Left[1], Top[1], Right[1], Color[0], camera_->transformationMatrixData, UV);
	myEngine->DrawSprite(LeftTop[0], LeftBottom[0], RightTop[0], RightBottom[0], Color[0], UV);
	myEngine->DrawSphere(sphere, camera_->transformationMatrixData,Color[0], SphereTexture);
	myEngine->DrawModel(modelData,{0,0,0}, camera_->transformationMatrixData,Color[0]);
	//描画ここまで
	myEngine->VertexReset();
}
