#include "WorldTransform.h"

void WorldTransform::Initialize()
{

	constBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(TransformationMatrix));
}

void WorldTransform::CreateConstBuffer()
{
	constBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(TransformationMatrix));
}

void WorldTransform::Map()
{
	constBuff_.Get()->Map(0, nullptr, reinterpret_cast<void**>(&constMap));
}

void WorldTransform::TransferMatrix()
{
	Matrix4x4 AffineMatrix = MakeAffineMatrix(scale_, rotation_, translation_);
	constMap->WVP = AffineMatrix;
	constMap->World = MakeIdentity4x4();
}
