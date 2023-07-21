#include"GameObject/Camera/DebugCamera.h"

void Debug::Initialize(int32_t kClientWidth, int32_t kClientHeight)
{
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;
	MatrixUpdate();
}

void Debug::Update()
{
	if (input->IspushKey(DIK_A)) {
		const float speed = -0.5f;
		Vector3 rotate{ speed,0,0 };
		rotation_ = Add(rotation_, rotate);
	}

	MatrixUpdate();

}

void Debug::MatrixUpdate()
{
	Matrix4x4 worldMatrix = MakeAffineMatrix({1,1,1}, {0,0,0}, {0,0,0});
	Matrix4x4 cameraMatrix = MakeAffineMatrix({1,1,1}, rotation_, translation_);
	ViewMatrix = Inverse(cameraMatrix);
	ProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kClientWidth_) / float(kClientHeight_), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(ViewMatrix, ProjectionMatrix));
	*transformationMatrixData = worldViewProjectionMatrix;
}
