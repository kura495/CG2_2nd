#include "WorldTransform.h"

void WorldTransform::Initialize()
{
	matWorld_.WVP = MakeIdentity4x4();
	matWorld_.World = MakeIdentity4x4();
	CreateConstBuffer();
	Map();
	TransferMatrix();
}

void WorldTransform::CreateConstBuffer()
{
	constBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(ConstBufferDataWorldTransform));
}

void WorldTransform::Map()
{
	constBuff_.Get()->Map(0, nullptr, reinterpret_cast<void**>(&constMap));
}

void WorldTransform::TransferMatrix()
{
	constMap->matWorld.WVP = matWorld_.WVP;
	constMap->matWorld.World = matWorld_.World;
}

void WorldTransform::UpdateMatrix()
{
	Matrix4x4 AffineMatrix = MakeAffineMatrix(scale_, rotation_, translation_);
	matWorld_.WVP = AffineMatrix;
	//親があれば親のワールド行列を掛ける
	if (parent_) {
		matWorld_.WVP = Multiply(matWorld_.WVP, parent_->matWorld_.WVP);
	}

	TransferMatrix();
}
