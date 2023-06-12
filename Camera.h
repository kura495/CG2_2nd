#pragma once
#include"MatrixCalc.h"
#include"Transform.h"
class Camera
{
public:
	void Initialize(int32_t kClientWidth, int32_t kClientHeight);
	void Update();
	Matrix4x4 transformationMatrixData;
private:
	Transform cameraTransform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,-10.0f},
	};
	Transform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	int32_t kClientWidth_;
	int32_t kClientHeight_;
};
