#pragma once
#include"DirectX.h"
#include"MatrixCalc.h"
#include"Matrix4x4.h"
#include"Transform.h"
class DrawEngine
{
public:
	void Initialize(DirectX* directX);

	void Draw(const Vector4& Leftbottom, const Vector4& top, const Vector4& Rightbottom, const Vector4& color, const Transform& transform);

	void Release();

private:
	HRESULT hr;
	DirectX* directX_=nullptr;
	//バーテックスリソース
	ID3D12Resource* vertexResource = nullptr;
	//頂点データ
	Vector4* vertexData=nullptr;
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
