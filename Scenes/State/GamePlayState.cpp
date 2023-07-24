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
	input = Input::GetInstance();
	Audio = XAudio2::GetInstance();
	//リソースを作る
	mokugyo = Audio->LoadAudio(L"resources/mokugyo.wav");
	UV = myEngine->LoadTexture("resources/uvChecker.png");
	Ball = myEngine->LoadTexture("resources/monsterBall.png");
	modelData = myEngine->LoadObjFile("resources", "Plane.obj");
	modelData2 = myEngine->LoadObjFile("resources", "Base.obj");
}
void GamePlayState::Update()
{
#ifdef _DEBUG
if (input->IspushKey(DIK_1)) {
		camera_->DebugCamera(true);
	}
	if (input->IspushKey(DIK_2)) {
	camera_->DebugCamera(false);
	}
#endif // _DEBUG

	

	camera_->Update();
	Audio->Play(mokugyo,0.1f,0);
}
void GamePlayState::Draw()
{
	//myEngine->Draw(Left[0], Top[0], Right[0], Color[0], camera_->GetWorldMatrix(), UV);
	myEngine->Draw(Left[1], Top[1], Right[1], Color[0], camera_->GetWorldMatrix(), UV);
	//myEngine->DrawSprite(LeftTop[0], LeftBottom[0], RightTop[0], RightBottom[0], Color[0], UV);
	myEngine->DrawSphere(sphere, camera_->GetWorldMatrix(),Color[0], SphereTexture);
	myEngine->DrawModel(modelData,{0,0,0}, camera_->GetWorldMatrix(),Color[0]);
	myEngine->DrawModel(modelData2,{0,0,0}, camera_->GetWorldMatrix(),Color[0]);
	if (input->IspushKey(DIK_0)) {
		OutputDebugStringA("Hit 0\n");
	}
	
	//描画ここまで
	myEngine->VertexReset();
}
