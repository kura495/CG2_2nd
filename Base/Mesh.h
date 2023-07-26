#include"IncludeStruct\Transform.h"
#include"DirectXCommon.h"
#include<wrl.h>
#include"IncludeStruct\VertexData.h"
#include"IncludeStruct\Material.h"
#include"IncludeStruct\TransformationMatrix.h"
#include"Math\MatrixCalc.h"
class Mesh
{
public:
	void Initialize();
	void Draw(const Vector4& Leftbottom, const Vector4& top, const Vector4& Rightbottom, const Vector4& color, const Matrix4x4& ViewMatrix, const int Index);
	void ImGui();
	void VecrtexReset();
private:
	DirectXCommon* directX_;

	static const int kMaxTriAngle = 3;
	static const int kMaxVertex = kMaxTriAngle * 3;
	bool IsusedTriAngleIndex[kMaxTriAngle];

	Transform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Transform uvTranformTriAngle{
	{1.0f,1.0f,1.0f},
	{0.0f,0.0f,0.0f},
	{0.0f,0.0f,0.0f}
	};
#pragma region TriAngle
	//バーテックスリソース
	Microsoft::WRL::ComPtr<ID3D12Resource>
		vertexResource = nullptr;
	//頂点データ
	VertexData* vertexData = nullptr;
	//バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	//色データ
	Material* materialData = nullptr;
	//WVPリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource = nullptr;
	//WVPデータ
	Matrix4x4* wvpData = nullptr;
	static const int kMaxTexture = 10;
	bool IsusedTextureIndex[kMaxTexture];
	//descriptorHandle
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU[kMaxTexture];
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU[kMaxTexture];
	void MakeVertexBufferView();
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
#pragma endregion 三角形
};
