#pragma once
#include"IgameState.h"
#include"Base/MyEngine.h"
#include"GameObject/Camera/Camera.h"
#include"IncludeStruct/ModelData.h"
#include"Audio/XAudio2.h"
#include"Input/Input.h"
#include"Base/Mesh.h"
#include"Base/Sprite.h"
#include"Base/Light.h"
#include"Base/Sphere.h"
#include"Base/TextureManager.h"
#include"Base/Model.h"
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include<dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class GamePlayState :public GameState
{
public:

	void Initialize();
	void Update();
	void Draw();
private:
	//基本機能ズ
	MyEngine* myEngine = nullptr;
	Camera* camera_ = nullptr;
	TextureManager* textureManager_ = nullptr;	
	Input* input = nullptr;
	XAudio2* Audio=nullptr;
	Light* light_ = nullptr;
	DirectXCommon* DirectX_ = nullptr;
	//
	//3Dオブジェクトたち
	Mesh* mesh = nullptr;
	Sphere* sphere = nullptr;
	Model* plane = nullptr;
	Model* teapot = nullptr;
	Model* bunny = nullptr;
	Model* multiMesh = nullptr;
	Model* multiMaterial = nullptr;
	Model* Suzanne = nullptr;
	Model* Base = nullptr;
	//2こめ
	Mesh* mesh2 = nullptr;
	Sphere* sphere2 = nullptr;
	Model* bunny2 = nullptr;
	Model* teapot2 = nullptr;
	//
	//2Dオブジェクトたち
	Sprite* sprite = nullptr;
	Sprite* sprite2 = nullptr;
	//
	//テクスチャハンドルたち
	uint32_t TextureHundle;
	uint32_t MonsterBall;
	//
	//サウンドハンドルたち
	uint32_t mokugyo;
	//

	//ImGui用フラッグ
	bool IsMeshFlag = false;
	bool IsSpriteFlag = false;
	bool IsSphereFlag = false;
	bool IsPlaneFlag = false;
	bool IsTeapotFlag = false;
	bool IsBunnyFlag = false;
	bool IsMultiMeshFlag = false;
	bool IsMultiMaterialFlag = false;
	bool IsSuzanneFlag = false;
	bool IsBaseFlag = false;
	bool IsLightFlag = false;
	bool IsCameraFlag = false;
	//２こめ
	bool IsChengePipeline = false;
	bool IsMesh2Flag = false;
	bool IsSprite2Flag = false;
	bool IsSphere2Flag = false;
	bool IsBunny2Flag = false;
	bool IsTeapot2Flag = false;
	//
	//Sprite用の位置
	Vector4 LeftTop[2] = {
		{ 0.0f,0.0f,0.0f,1.0f },
		{ 320.0f,0.0f,0.0f,1.0f }
	};
	Vector4 LeftBottom[2] = {
		{ 0.0f,180.0f,0.0f,1.0f },
		{ 320.0f,180.0f,0.0f,1.0f }
	};
	Vector4 RightTop[2] = {
		{ 320.0f,0.0f,0.0f,1.0f },
		{ 640.0f,0.0f,0.0f,1.0f }
	};
	Vector4 RightBottom[2] = {
		{ 320.0f,180.0f,0.0f,1.0f },
		{ 640.0f,180.0f,0.0f,1.0f }
	};
	//
};