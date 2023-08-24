#include "Player.h"

void Player::Initialize()
{
	input = Input::GetInstance();
	model = Model::CreateModelFromObj("resources","bunny.obj");
	
	worldTransform_.Initialize();


	const char* groupName = "Player";

	//GlobalVariables::GetInstance()->CreateGroup(groupName);
	GlobalVariables::GetInstance()->AddItem(groupName,"speed",speed);
}

void Player::Update()
{
	if (input->IspushKey(DIK_W)) {
		worldTransform_.translation_.z += 0.5f * speed;
	}
	else if (input->IspushKey(DIK_S)) {
		worldTransform_.translation_.z -= 0.5f * speed;
	}
	worldTransform_.UpdateMatrix();
	ApplyGlobalVariables();
}

void Player::Draw(const ViewProjection& viewProjection)
{
	model->Draw(worldTransform_, viewProjection);
}

void Player::ApplyGlobalVariables()
{
	const char* groupName = "Player";
	speed = GlobalVariables::GetInstance()->GetfloatValue(groupName, "speed");
}
