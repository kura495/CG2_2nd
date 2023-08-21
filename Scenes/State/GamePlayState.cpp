#include"Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	//基本機能生成
	camera_ = new Camera();
	camera_->Initialize(1280, 720);
	input = Input::GetInstance();
	Audio = XAudio2::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();
	DirectX_ = DirectXCommon::GetInstance();
	//
	//3Dオブジェクト生成
	player = new Player();
	player->Initialize();
	//
	//2Dオブジェクト作成

	//
	//リソースを作る
	//テクスチャ

	//サウンド
	mokugyo = Audio->LoadAudio(L"resources/mokugyo.wav");
	//
}
void GamePlayState::Update()
{
#ifdef _DEBUG
if (input->IspushKey(DIK_LALT)) {
		camera_->DebugCamera(true);
}
else {
	camera_->DebugCamera(false);
}
#endif // _DEBUG
	GlobalVariables::GetInstance()->Update();

	ImGui::Begin("Sound");
	ImGui::SliderInt("Pan", &Pan, 1, -1);
	ImGui::SliderFloat("Volume",&Volume,0.0f,1.0f);
	Audio->Play(mokugyo, Volume, Pan);
	ImGui::End();
	camera_->Update();
	
	player->Update();
}
void GamePlayState::Draw()
{
	player->Draw(camera_->GetWorldMatrix());
	//1. ビット演算を取り回しの良いUtilityクラスにする
	//2. 三項演算子をつかって、構造がわかりやすいようにする
	//piplineStatus->GetIsMesh2() ? mesh2->Draw() : ;
	//piplineStatus->GetIsSprite() ? sprite->Draw() : ;
	//piplineStatus->SetAllFlags();

	//void PipelineStatu::SetAllFlags() {
	//	bit = 0x111111111111.....;
	//}

	//void PipelineStatus::ResetAllFlags() {
		//Ethna
	//	bit = 0;
	//}
	
	
	//描画ここまで
}
