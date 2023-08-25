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
		worldTransform_.translation_.y += 0.5f * speed;
	}
	else if (input->IspushKey(DIK_S)) {
		worldTransform_.translation_.y -= 0.5f * speed;
	}
	if (input->IspushKey(DIK_A)) {
		worldTransform_.translation_.x -= 0.5f * speed;
	}
	else if (input->IspushKey(DIK_D)) {
		worldTransform_.translation_.x += 0.5f * speed;
	}
	if (input->IspushKey(DIK_Q)) {
		worldTransform_.translation_.z += 0.5f * speed;
	}
	else if (input->IspushKey(DIK_E)) {
		worldTransform_.translation_.z -= 0.5f * speed;
	}
	if (input->IspushKey(DIK_1)) {
		worldTransform_.scale_.x -= 0.5f * speed;
		worldTransform_.scale_.y -= 0.5f * speed;
		worldTransform_.scale_.z -= 0.5f * speed;
	}
	else if (input->IspushKey(DIK_2)) {
		worldTransform_.scale_.x += 0.5f * speed;
		worldTransform_.scale_.y += 0.5f * speed;
		worldTransform_.scale_.z += 0.5f * speed;
	}
	
	ImGui();
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

void Player::ImGui()
{
	ImGui::Begin("Player");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x,-10, 10);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x,-10, 10);
	ImGui::SliderFloat3("scale", &worldTransform_.scale_.x,-10, 10);
	ImGui::End();
}
