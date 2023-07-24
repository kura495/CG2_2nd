#pragma once
#include"DirectXCommon.h"
class Mesh
{
public:
	void Initialize(DirectXCommon* directX);
	void Draw();
	void Release();
	/// <summary>
	/// 0=左下
	/// 1=上
	/// 2=右下
	/// </summary>
	Vector4* vertexData=nullptr;
private:
	HRESULT hr;
	DirectXCommon* directX_=nullptr;
	//バーテックスリソース
	ID3D12Resource* vertexResource = nullptr;
	//バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	
	void MakeVertexResource();
	void MakeVertexBufferView();
};
