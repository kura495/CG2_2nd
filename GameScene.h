#pragma once
#include"MyEngine.h"
#include"Camera.h"
#include"ImGuiManager.h"
class GameScene
{
public:
	void Initialize(DirectXCommon* directX, MyEngine* myEngine,WinApp* winApp, int32_t kClientWidth,int32_t kClientHeight);

	void UpDate();

	void Draw();

	void Release();
	
private:
	int32_t kClientWidth_=0;
	int32_t kClientHeight_=0;
	DirectXCommon* directX_ = nullptr;
	MyEngine* myEngine_ = nullptr;
	Camera* camera_ = nullptr;
	ImGuiManager* ImGuiManager_ = nullptr;
	Vector4 Left[3] = { 
	 {-0.5f,-0.5f,0.0f,1.0f} 
	,{-0.5f,-1.5f,0.0f,1.0f}
	,{1.0f,-0.5f,0.0f,1.0f} };
	Vector4 Top[3] = { 
	 {0.0f,0.5f,0.0f,1.0f}
	,{0.0f,-0.5f,0.0f,1.0f}
	,{1.5f,0.5f,0.0f,1.0f} };
	Vector4 Right[3] ={ 
	 {0.5f,-0.5f,0.0f,1.0f}
	,{0.5f,-1.5f,0.0f,1.0f}
	,{2.0f,-0.5f,0.0f,1.0f} };
	Vector4 Color[2] = {1.0f,1.0f,1.0f,1.0f};
	//Sprite

	Vector4 LeftTop = { 0.0f,0.0f,0.0f,1.0f };
	Vector4 LeftBottom = { 0.0f,360.0f,0.0f,1.0f };
	Vector4 RightTop = { 640.0f,0.0f,0.0f,1.0f };
	Vector4 RightBottom = { 640.0f,360.0f,0.0f,1.0f };
	Sphere sphere{
		{0.0f,0.0f,0.0f},
		16
	};
	int UV;
	int Ball;
	int Max;
	bool useMonsterBall = true;
	int SphereTexture = 0;
	
};

