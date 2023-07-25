#include"IncludeStruct\Transform.h"
#include"DirectXCommon.h"
#include<wrl.h>
#include"IncludeStruct\VertexData.h"
#include"IncludeStruct\Material.h"
#include"Math\MatrixCalc.h"
class Mesh
{
public:
	void Initialize();
	void Draw(const Vector4& Leftbottom, const Vector4& top, const Vector4& Rightbottom, const Vector4& color, const Matrix4x4& ViewMatrix, const int Index);
	void ImGui();

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
	//�o�[�e�b�N�X���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource>
		vertexResource = nullptr;
	//���_�f�[�^
	VertexData* vertexData = nullptr;
	//�o�[�e�b�N�X�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//�}�e���A�����\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	//�F�f�[�^
	Material* materialData = nullptr;
	//WVP���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource = nullptr;
	//WVP�f�[�^
	Matrix4x4* wvpData = nullptr;
	void MakeVertexBufferView();
#pragma endregion �O�p�`
};
