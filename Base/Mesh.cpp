#include"Mesh.h"

void Mesh::Initialize()
{
	vertexResource = CreateBufferResource(sizeof(VertexData) * kMaxVertex);
	materialResource = CreateBufferResource(sizeof(Material) * kMaxTriAngle);
	wvpResource = CreateBufferResource(sizeof(TransformationMatrix));
	MakeVertexBufferView();
}

void Mesh::Draw(const Vector4& Leftbottom, const Vector4& top, const Vector4& Rightbottom, const Vector4& color, const Matrix4x4& ViewMatrix, const int Index)
{
	int TriAngleIndex = kMaxVertex + 1;
	for (int i = 0; i < kMaxTriAngle; ++i) {
		if (IsusedTriAngleIndex[i] == false) {
			TriAngleIndex = i * 3;
			IsusedTriAngleIndex[i] = true;
			break;
		}
	}
	if (TriAngleIndex < 0) {
		//0��菭�Ȃ�
		assert(false);
	}
	if (kMaxVertex < TriAngleIndex) {
		//MaxSprite��葽��
		assert(false);
	}
	vertexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//����
	vertexData[TriAngleIndex].position = Leftbottom;
	vertexData[TriAngleIndex].texcoord = { 0.0f,1.0f };
	//��
	vertexData[TriAngleIndex + 1].position = top;
	vertexData[TriAngleIndex + 1].texcoord = { 0.5f,0.0f };
	//�E��
	vertexData[TriAngleIndex + 2].position = Rightbottom;
	vertexData[TriAngleIndex + 2].texcoord = { 1.0f,1.0f };

	//�F���������ރA�h���X���擾
	materialResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	//�F������������
	materialData->color = color;
	materialData->enableLighting = false;
	materialData->uvTransform = MakeIdentity4x4();
	Matrix4x4 uvTransformMatrix = MakeScaleMatrix(uvTranformTriAngle.scale);
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeRotateZMatrix(uvTranformTriAngle.rotate.z));
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeTranslateMatrix(uvTranformTriAngle.translate));
	materialData->uvTransform = uvTransformMatrix;
	//�s������
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
	//WVP���������ރA�h���X���擾
	wvpResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
	//�P�ʍs�����������
	*wvpData = Multiply(worldMatrix, ViewMatrix);
	directX_->GetcommandList().Get()->IASetVertexBuffers(0, 1, &vertexBufferView);
	directX_->GetcommandList().Get()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//�F�p��CBuffer�̏ꏊ�����
	directX_->GetcommandList().Get()->SetGraphicsRootConstantBufferView(0, materialResource.Get()->GetGPUVirtualAddress());
	//WVP�p��CBuffer�̏ꏊ�����
	directX_->GetcommandList().Get()->SetGraphicsRootConstantBufferView(1, wvpResource.Get()->GetGPUVirtualAddress());
	//SRV��DescriptorTable�̐擪��ݒ�@2��rootParameter[2]��2
	directX_->GetcommandList().Get()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU[Index]);
	directX_->GetcommandList().Get()->DrawInstanced(TriAngleIndex + 3, 1, 0, 0);
}

void Mesh::ImGui()
{
#pragma region TriAngleImGui
	ImGui::ShowDemoWindow();

	ImGui::Begin("TriAngle");
	float ImGuiScale[Vector3D] = { transform.scale.x,transform.scale.y ,transform.scale.z };
	ImGui::SliderFloat3("Scale", ImGuiScale, 1, 30, "%.3f");
	transform.scale = { ImGuiScale[x],ImGuiScale[y],ImGuiScale[z] };
	float ImGuiRotate[Vector3D] = { transform.rotate.x,transform.rotate.y ,transform.rotate.z };
	ImGui::SliderFloat3("Rotate", ImGuiRotate, -7, 7, "%.3f");
	transform.rotate = { ImGuiRotate[x],ImGuiRotate[y],ImGuiRotate[z] };
	float ImGuiTranslate[Vector3D] = { transform.translate.x,transform.translate.y ,transform.translate.z };
	ImGui::SliderFloat3("Translate", ImGuiTranslate, -2, 2, "%.3f");
	transform.translate = { ImGuiTranslate[x],ImGuiTranslate[y],ImGuiTranslate[z] };
	ImGui::DragFloat2("UVTranslate", &uvTranformTriAngle.translate.x, 0.01f, -10.0f, 10.0f);
	ImGui::DragFloat2("UVScale", &uvTranformTriAngle.scale.x, 0.01f, -10.0f, 10.0f);
	ImGui::SliderAngle("UVRotate", &uvTranformTriAngle.rotate.z);
	ImGui::End();
#pragma endregion
}

void Mesh::MakeVertexBufferView()
{
	vertexBufferView.BufferLocation = vertexResource.Get()->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(VertexData) * kMaxVertex;
	vertexBufferView.StrideInBytes = sizeof(VertexData);
}
