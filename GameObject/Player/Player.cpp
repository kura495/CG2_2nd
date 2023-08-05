#include "Player.h"

void Player::Initialize(Model* model_)
{
	model = model_;
}

void Player::Update()
{
	AffineMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
}

void Player::Draw(const Matrix4x4& ViewMatrix)
{
	model->DrawModel(AffineMatrix, ViewMatrix);
}
