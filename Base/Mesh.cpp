﻿#include"Mesh.h"
void Mesh::Initialize()
{
	directX_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	vertexResource = directX_->CreateBufferResource(sizeof(VertexData)*3);
	materialResource = directX_->CreateBufferResource(sizeof(Material));
	MakeVertexBufferView();
	vertexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//左下
	vertexData[0].position = { -0.5f,0.0f,0.0f,1.0f };
	vertexData[0].texcoord = { 0.0f,1.0f };
	//上
	vertexData[1].position = { 0.0f,1.0f,0.0f,1.0f };
	vertexData[1].texcoord = { 0.5f,0.0f };
	//右下
	vertexData[2].position = { 0.5f,0.0f,0.0f,1.0f };
	vertexData[2].texcoord = { 1.0f,1.0f };
}

void Mesh::Draw(const WorldTransform& transform, const ViewProjection& viewProjection, const uint32_t textureHandle)
{
	//色を書き込むアドレスを取得
	materialResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	//色情報を書き込む
	materialData->color = color_;
	materialData->enableLighting = false;
	materialData->uvTransform = MakeIdentity4x4();
	Matrix4x4 uvTransformMatrix = MakeScaleMatrix(uvTranformTriAngle.scale);
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeRotateZMatrix(uvTranformTriAngle.rotate.z));
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeTranslateMatrix(uvTranformTriAngle.translate));
	materialData->uvTransform = uvTransformMatrix;
	
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//色用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResource.Get()->GetGPUVirtualAddress());
	//WVP
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transform.constBuff_->GetGPUVirtualAddress());
	//ViewProjection
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(4, viewProjection.constBuff_->GetGPUVirtualAddress());
	//SRVのDescriptorTableの先頭を設定　2はrootParameter[2]の2
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(textureHandle));
	directX_->GetcommandList()->DrawInstanced(3, 1, 0, 0);
}

void Mesh::MakeVertexBufferView()
{
	vertexBufferView.BufferLocation = vertexResource.Get()->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(VertexData) * 3;
	vertexBufferView.StrideInBytes = sizeof(VertexData);
}


