#include"Sprite.h"
void Sprite::Initialize(const Vector4& LeftTop, const Vector4& LeftBottom, const Vector4& RightTop, const Vector4& RightBottom)
{
	directX_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	vertexResourceSprite = directX_->CreateBufferResource(sizeof(VertexData) * 4);
	materialResourceSprite = directX_->CreateBufferResource(sizeof(Material));

	MakeVertexBufferViewSprite();
	indexResourceSprite = directX_->CreateBufferResource(sizeof(uint32_t) * 6);
	MakeIndexBufferViewSprite();

	vertexResourceSprite.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSprite));

	//左下
	vertexDataSprite[0].position = LeftBottom;
	vertexDataSprite[0].texcoord = { 0.0f,1.0f };
	//左上
	vertexDataSprite[1].position = LeftTop;
	vertexDataSprite[1].texcoord = { 0.0f,0.0f };
	//右下
	vertexDataSprite[2].position = RightBottom;
	vertexDataSprite[2].texcoord = { 1.0f,1.0f };
	//右上
	vertexDataSprite[3].position = RightTop;
	vertexDataSprite[3].texcoord = { 1.0f,0.0f };

	//インデックスリソースにデータを書き込む
	indexResourceSprite.Get()->Map(0, nullptr, reinterpret_cast<void**>(&indexDataSprite));

	//三角形1枚目
	indexDataSprite[0] = 0;
	indexDataSprite[1] = 1;
	indexDataSprite[2] = 2;
	//三角形2枚目
	indexDataSprite[3] = 1;
	indexDataSprite[4] = 3;
	indexDataSprite[5] = 2;
}

void Sprite::DrawSprite(const WorldTransform& transform,const uint32_t TextureHandle)
{

	//色の書き込み
	materialResourceSprite.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialDataSprite));
	materialDataSprite->color = color_;
	//ライティングをしない
	materialDataSprite->enableLighting = false;
	materialDataSprite->uvTransform = MakeIdentity4x4();
	Matrix4x4 uvTransformMatrix = MakeScaleMatrix(uvTranformSprite.scale);
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeRotateZMatrix(uvTranformSprite.rotate.z));
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeTranslateMatrix(uvTranformSprite.translate));
	materialDataSprite->uvTransform = uvTransformMatrix;



	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSprite);
	directX_->GetcommandList()->IASetIndexBuffer(&indexBufferViewSprite);
	//色用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSprite.Get()->GetGPUVirtualAddress());
	//WVP用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transform.constBuff_.Get()->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(TextureHandle));

	directX_->GetcommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void Sprite::MakeVertexBufferViewSprite()
{
	//リソースの先頭のアドレス
	vertexBufferViewSprite.BufferLocation = vertexResourceSprite.Get()->GetGPUVirtualAddress();
	//使用する頂点サイズ
	vertexBufferViewSprite.SizeInBytes = sizeof(VertexData) * 4;
	//1頂点あたりのアドレス
	vertexBufferViewSprite.StrideInBytes = sizeof(VertexData);
}
void Sprite::MakeIndexBufferViewSprite()
{
	//リソース先頭アドレス
	indexBufferViewSprite.BufferLocation = indexResourceSprite.Get()->GetGPUVirtualAddress();
	//使用するインデックスサイズ
	indexBufferViewSprite.SizeInBytes = sizeof(uint32_t) * 6;
	//インデックスはuint32_t
	indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;
}