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
	DirectX_ = DirectXCommon::GetInstance();
	//
	//3Dオブジェクト生成
	mesh = new Mesh();
	mesh->Initialize();
	sphere = new Sphere();
	sphere->Initialize();
	plane=Model::CreateModelFromObj("resources", "plane.obj");
	teapot = Model::CreateModelFromObj("resources", "teapot.obj");
	bunny = Model::CreateModelFromObj("resources", "bunny.obj");
	multiMesh = Model::CreateModelFromObj("resources", "multiMesh.obj");
	multiMaterial = Model::CreateModelFromObj("resources", "multiMaterial.obj");
	Base = Model::CreateModelFromObj("resources", "Base.obj");
	bunny2= Model::CreateModelFromObj("resources", "bunny.obj");
	//Suzanne = Model::CreateModelFromObj("resources", "suzanne.obj");
	//
	//2Dオブジェクト作成
	sprite = new Sprite();
	sprite->Initialize({0.0f,0.0f,0.0f,1.0f},{0.0f,360.0f,0.0f,1.0f},{640.0f,0.0f,0.0f,1.0f},{640.0f,360.0f,0.0f,1.0f});
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
	ImGui::Begin("Button");
	if (ImGui::Button("Mesh")) {
		if (IsMeshFlag) {
			IsMeshFlag = false;
		}
		else {
			IsMeshFlag = true;
		}
	}
	if (ImGui::Button("Sprite")) {
		if (IsSpriteFlag) {
			IsSpriteFlag = false;
		}
		else {
			IsSpriteFlag = true;
		}
	}
	if (ImGui::Button("Sphere")) {
		if (IsSphereFlag) {
			IsSphereFlag = false;
		}
		else {
			IsSphereFlag = true;
		}
	}
	if (ImGui::Button("Plane")) {
		if (IsPlaneFlag) {
			IsPlaneFlag = false;
		}
		else {
			IsPlaneFlag = true;
		}
	}
	if (ImGui::Button("Teapot")) {
		if (IsTeapotFlag) {
			IsTeapotFlag = false;
		}
		else {
			IsTeapotFlag = true;
		}
	}
	if (ImGui::Button("bunny")) {
		if (IsBunnyFlag) {
			IsBunnyFlag = false;
		}
		else {
			IsBunnyFlag = true;
		}
	}
	if (ImGui::Button("multiMesh")) {
		if (IsMultiMeshFlag) {
			IsMultiMeshFlag = false;
		}
		else {
			IsMultiMeshFlag = true;
		}
	}
	if (ImGui::Button("multiMaterial")) {
		if (IsMultiMaterialFlag) {
			IsMultiMaterialFlag = false;
		}
		else {
			IsMultiMaterialFlag = true;
		}
	}
	if (ImGui::Button("Base")) {
		if (IsBaseFlag) {
			IsBaseFlag = false;
		}
		else {
			IsBaseFlag = true;
		}
	}
	if (ImGui::Button("ChengePipeline")) {
		if (IsChengePipeline) {
			IsChengePipeline = false;
		}
		else {
			IsChengePipeline = true;
		}
	}

	if (ImGui::Button("Light")) {
		if (IsLightFlag) {
			IsLightFlag = false;
		}
		else {
			IsLightFlag = true;
		}
	}
	if (ImGui::Button("Camera")) {
		if (IsCameraFlag) {
			IsCameraFlag = false;
		}
		else {
			IsCameraFlag = true;
		}
	}

	if (IsMeshFlag) {
		mesh->ImGui("TriAngle");
	}
	if (IsSpriteFlag) {
		sprite->ImGui("Sprite");
	}
	if (IsSphereFlag) {
		sphere->ImGui("Sphere");
	}
	if (IsPlaneFlag) {
		plane->ImGui("Plane");
	}
	if (IsTeapotFlag) {
		teapot->ImGui("teapot");
	}
	if (IsBunnyFlag) {
		bunny->ImGui("bunny");
	}
	if (IsMultiMeshFlag) {
		multiMesh->ImGui("multiMesh");
	}
	if (IsMultiMaterialFlag) {
		multiMaterial->ImGui("multiMaterial");
	}
	if (IsBaseFlag) {
		Base->ImGui("Base");
	}
	if (IsLightFlag) {
		light_->ImGui("Light");
	}
	if (IsCameraFlag) {
		camera_->ImGui("camera");
	}
	ImGui::End();
	bunny2->ImGui("bunny2");
	//Audio->Play(mokugyo,0.1f,0);
	camera_->Update();
	
	
}
void GamePlayState::Draw()
{
	
	if (IsMeshFlag){
		mesh->Draw(camera_->GetWorldMatrix(),TextureHundle);
	}
	if (IsSpriteFlag){
		sprite->DrawSprite(TextureHundle);
	}
	if (IsSphereFlag) {
		sphere->DrawSphere(camera_->GetWorldMatrix(), TextureHundle);
	}
	if (IsPlaneFlag) {
		plane->DrawModel(camera_->GetWorldMatrix());
	}
	if (IsTeapotFlag) {
		teapot->DrawModel( camera_->GetWorldMatrix());
	}
	if (IsBunnyFlag) {
		bunny->DrawModel( camera_->GetWorldMatrix());
	}
	if (IsMultiMeshFlag) {
		multiMesh->DrawModel( camera_->GetWorldMatrix());
	}
	if (IsMultiMaterialFlag) {
		multiMaterial->DrawModel( camera_->GetWorldMatrix());
	}
	if (IsBaseFlag) {
		Base->DrawModel( camera_->GetWorldMatrix());
	}
	if (IsChengePipeline) {
		DirectX_->PostProsessDraw();
	}
	
	bunny2->DrawModel(camera_->GetWorldMatrix());
	
	
	//描画ここまで
}
