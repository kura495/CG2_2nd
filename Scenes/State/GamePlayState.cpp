#include"Scenes/State/GamePlayState.h"

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
	sprite = new Sprite();
	sprite->Initialize(LeftTop[0],LeftBottom[0],RightTop[0], RightBottom[0]);
	sprite2 = new Sprite();
	sprite2->Initialize(LeftTop[1],LeftBottom[1],RightTop[1], RightBottom[1]);
	textureManager_ = TextureManager::GetInstance();
	//リソースを作る
	mokugyo = Audio->LoadAudio(L"resources/mokugyo.wav");
	TextureHundle = textureManager_->LoadTexture("resources/uvChecker.png");
	MonsterBall = textureManager_->LoadTexture("resources/monsterBall.png");
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
	sprite->ImGui("Sprite");
	sprite2->ImGui("Sprite2");
	
	Audio->Play(mokugyo,0.1f,0);

	camera_->ImGui();
	camera_->Update();
}
void GamePlayState::Draw()
{
	mesh->Draw(Color[0],camera_->GetWorldMatrix(), TextureHundle);
	mesh2->Draw(Color[0],camera_->GetWorldMatrix(), MonsterBall);
	sprite->DrawSprite(Color[0],TextureHundle);
	sprite2->DrawSprite(Color[0], MonsterBall);

	if (input->IspushKey(DIK_0)) {
		OutputDebugStringA("Hit 0\n");
	}
	
	//描画ここまで
}
