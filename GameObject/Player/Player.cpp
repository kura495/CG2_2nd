#include "Player.h"

void Player::Initialize()
{
	input = Input::GetInstance();
	model = Model::CreateModelFromObj("resources","bunny.obj");
	const char* groupName = "Player";

	//GlobalVariables::GetInstance()->CreateGroup(groupName);
	GlobalVariables::GetInstance()->AddItem(groupName,"speed",speed);
}

void Player::Update()
{
	if (input->IspushKey(DIK_W)) {
		transform.translate.z += 0.5f * speed;
	}
	else if (input->IspushKey(DIK_S)) {
		transform.translate.z -= 0.5f * speed;
	}
	AffineMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
	ApplyGlobalVariables();
}

void Player::Draw(const Matrix4x4& ViewMatrix)
{
	model->DrawModel(AffineMatrix, ViewMatrix);
}

void Player::ApplyGlobalVariables()
{
	const char* groupName = "Player";
	speed = GlobalVariables::GetInstance()->GetfloatValue(groupName, "speed");
}
