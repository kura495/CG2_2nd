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
	//インスタンス生成する
	camera_ = new Camera();
	camera_->Initialize(1280, 720);
	myEngine = MyEngine::GetInstance();
	input = Input::GetInstance();
	Audio = XAudio2::GetInstance();
	mesh = new Mesh();
	mesh->Initialize();
	mesh2 = new Mesh();
	mesh2->Initialize();
	textureManager_ = TextureManager::GetInstance();
	//リソースを作る
	mokugyo = Audio->LoadAudio(L"resources/mokugyo.wav");
	TextureHundle = textureManager_->LoadTexture("resources/uvChecker.png");
	Monster = textureManager_->LoadTexture("resources/monsterBall.png");
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

	mesh->ImGui("TriAngle");
	mesh2->ImGui("TriAngle2");
	
	
	Audio->Play(mokugyo,0.1f,0);

	camera_->ImGui();
	camera_->Update();
}
void GamePlayState::Draw()
{
	mesh->Draw(Color[0],camera_->GetWorldMatrix(), TextureHundle);
	mesh2->Draw(Color[0],camera_->GetWorldMatrix(), Monster);

	if (input->IspushKey(DIK_0)) {
		OutputDebugStringA("Hit 0\n");
	}
	
	//描画ここまで
}
