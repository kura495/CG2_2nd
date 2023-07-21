#pragma once
#include"includeStruct/Vector3.h"
#include"includeStruct/Matrix4x4.h"
#include"includeStruct/Transform.h"
#include"Math/MatrixCalc.h"
#include"Input/Input.h"
class Debug
{
public:
	void Initialize(int32_t kClientWidth, int32_t kClientHeight);

	void Update();

private:
	void MatrixUpdate();
	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation_ = { 0,0,0 };
	// ローカル座標
	Vector3 translation_ = {0,0,-50};
	//　ビュー行列
	Matrix4x4 ViewMatrix;
	// 射影行列
	Matrix4x4 ProjectionMatrix;
	// 
	Matrix4x4 worldMatrix;
	Input* input=nullptr;
	int32_t kClientWidth_;
	int32_t kClientHeight_;
	Matrix4x4* transformationMatrixData;
};

