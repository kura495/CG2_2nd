#pragma once
#include"DirectXCommon.h"
#include"MatrixCalc.h"
#include"Matrix4x4.h"
#include"Transform.h"
class MyEngine
{
public:
	void Initialize(DirectXCommon* directX);

	void Draw(const Vector4& Leftbottom, const Vector4& top, const Vector4& Rightbottom, const Vector4& color, const Transform& transform,const Matrix4x4& ViewMatrix);

	void Release();

private:
	HRESULT hr;
	DirectXCommon* directX_=nullptr;
	//バーテックスリソース
	ID3D12Resource* vertexResource = nullptr;
	//頂点データ
	Vector4* vertexData;
	//バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//マテリアルリソース
	ID3D12Resource* materialResource = nullptr;
	//色データ
	Vector4* materialData = nullptr;
	//WVPリソース
	ID3D12Resource* wvpResource = nullptr;
	//WVPデータ
	Matrix4x4* wvpData = nullptr;
	
	void MakeVertexResource();
	void MakeVertexBufferView();
	ID3D12Resource* CreateBufferResource(size_t sizeInBytes);
};
