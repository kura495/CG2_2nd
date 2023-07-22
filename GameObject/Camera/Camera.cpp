#include"Camera.h"

void Camera::Initialize(int32_t kClientWidth, int32_t kClientHeight)
{
	kClientWidth_= kClientWidth;
	kClientHeight_= kClientHeight;
	worldMatrix = MakeAffineMatrix({1,1,1},{0,0,0}, {0,0,0});
	Matrix4x4 cameraMatrix = MakeAffineMatrix({1,1,1},rotation_,translation_);
	ViewMatrix = Inverse(cameraMatrix);
	ProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kClientWidth_) / float(kClientHeight_), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix,Multiply(ViewMatrix, ProjectionMatrix));
	transformationMatrixData = worldViewProjectionMatrix;
}
void Camera::Update()
{

	worldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0,0,0 });
	Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1,1,1 }, rotation_, translation_);
	ViewMatrix = Inverse(cameraMatrix);
	ProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kClientWidth_) / float(kClientHeight_), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(ViewMatrix, ProjectionMatrix));
	transformationMatrixData = worldViewProjectionMatrix;
#ifdef _DEBUG
DebugCameraMove();
#endif // _DEBUG

	
}
void Camera::ImGui()
{
	ImGui::Begin("Camera");
	float ImGuiRotate[Vector3D] = { rotation_.x,rotation_.y ,rotation_.z };
	ImGui::SliderFloat3("Rotate", ImGuiRotate, 0, 5, "%.3f");
	rotation_ = { ImGuiRotate[x],ImGuiRotate[y],ImGuiRotate[z] };
	float ImGuiTranslate[Vector3D] = { translation_.x,translation_.y ,translation_.z };
	ImGui::SliderFloat3("Translate", ImGuiTranslate, -10, 10, "%.3f");
	translation_ = { ImGuiTranslate[x],ImGuiTranslate[y],ImGuiTranslate[z] };
#ifdef _DEBUG
	ImGui::Text("DebugCamera : 0\n");
	ImGui::Text("Rotate : W A S D\n");
	ImGui::Text("Translate : ARROWKEY\n");
#endif // DEBUG

	ImGui::End();
}

#ifdef _DEBUG
void Camera::DebugCameraMove()
{
#pragma region rotation
	if (DebucCameraFlag) {
		if (input->IspushKey(DIK_A)) {
			const float speed = -0.5f;
			Vector3 rotate{ speed,0,0 };
			rotation_ = Add(rotation_, rotate);
		}
		else if (input->IspushKey(DIK_D)) {
			const float speed = 0.5f;
			Vector3 rotate{ speed,0,0 };
			rotation_ = Add(rotation_, rotate);
		}
		if (input->IspushKey(DIK_W)) {
			const float speed = 0.5f;
			Vector3 rotate{ 0,speed,0 };
			rotation_ = Add(rotation_, rotate);
		}
		else if (input->IspushKey(DIK_S)) {
			const float speed = -0.5f;
			Vector3 rotate{ 0,speed,0 };
			rotation_ = Add(rotation_, rotate);
		}
	}
#pragma endregion 回転
#pragma region translation_
	if (DebucCameraFlag) {
		if (input->IspushKey(DIK_LEFT)) {
			const float speed = -0.5f;
			Vector3 translate{ speed,0,0 };
			translation_ = Add(translation_, translate);
		}
		else if (input->IspushKey(DIK_RIGHT)) {
			const float speed = 0.5f;
			Vector3 translate{ speed,0,0 };
			translation_ = Add(translation_, translate);
		}
		if (input->IspushKey(DIK_UP)) {
			const float speed = -0.5f;
			Vector3 translate{ 0,speed,0 };
			translation_ = Add(translation_, translate);
		}
		else if (input->IspushKey(DIK_DOWN)) {
			const float speed = 0.5f;
			Vector3 translate{ 0,speed,0 };
			translation_ = Add(translation_, translate);
		}
	}
#pragma endregion 移動
}
#endif // DEBUG