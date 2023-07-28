#include"Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	//基本機能生成
	camera_ = new Camera();
	camera_->Initialize(1280, 720);
	myEngine = MyEngine::GetInstance();
	input = Input::GetInstance();
	Audio = XAudio2::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();
	//
	//3Dオブジェクト生成
	mesh = new Mesh();
	mesh->Initialize();
	mesh2 = new Mesh();
	mesh2->Initialize();
	sphere = new Sphere();
	sphere->Initialize();
	sphere2 = new Sphere();
	sphere2->Initialize();
	modelData=Model::CreateModelFromObj("resources", "teapot.obj");
	modelData2 = Model::CreateModelFromObj("resources", "bunny.obj");
	//
	//2Dオブジェクト作成
	sprite = new Sprite();
	sprite->Initialize(LeftTop[0],LeftBottom[0],RightTop[0], RightBottom[0]);
	sprite2 = new Sprite();
	sprite2->Initialize(LeftTop[1],LeftBottom[1],RightTop[1], RightBottom[1]);
	//
	//リソースを作る
	//テクスチャ
	TextureHundle = textureManager_->LoadTexture("resources/uvChecker.png");
	MonsterBall = textureManager_->LoadTexture("resources/monsterBall.png");
	//サウンド
	mokugyo = Audio->LoadAudio(L"resources/mokugyo.wav");
	//
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

	//mesh->ImGui("TriAngle");
	//mesh2->ImGui("TriAngle2");
	//sprite->ImGui("Sprite");
	//sprite2->ImGui("Sprite2");
	//sphere->ImGui("Sphere");
	//sphere2->ImGui("Sphere2");
	//light_->ImGui("Light");
	modelData->ImGui("Model");
	modelData2->ImGui("Model2");
	Audio->Play(mokugyo,0.1f,0);

	camera_->ImGui();
	camera_->Update();
}
void GamePlayState::Draw()
{
	//mesh->Draw(Color[0],camera_->GetWorldMatrix(), TextureHundle);
	//mesh2->Draw(Color[0],camera_->GetWorldMatrix(), MonsterBall);
	//sprite->DrawSprite(Color[0],TextureHundle);
	//sprite2->DrawSprite(Color[0], MonsterBall);
	//sphere->DrawSphere(Color[0],camera_->GetWorldMatrix(), TextureHundle);
	//sphere2->DrawSphere(Color[0],camera_->GetWorldMatrix(), MonsterBall);
	modelData->DrawModel(camera_->GetWorldMatrix(),Color[0]);
	modelData2->DrawModel( camera_->GetWorldMatrix(),Color[0]);

	if (input->IspushKey(DIK_0)) {
		OutputDebugStringA("Hit 0\n");
	}
	
	//描画ここまで
}
