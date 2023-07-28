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
	//
	//3Dオブジェクトたち
	Mesh* mesh = nullptr;
	Mesh* mesh2 = nullptr;
	Sphere* sphere = nullptr;
	Sphere* sphere2 = nullptr;
	Model* modelData = nullptr;
	Model* modelData2 = nullptr;
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

	Vector4 Color[2] = { 1.0f,1.0f,1.0f,1.0f };
	//Sprite用の位置
	Vector4 LeftTop[2] = {
		{ 0.0f,0.0f,0.0f,1.0f },
		{ 640.0f,0.0f,0.0f,1.0f }
	};
	Vector4 LeftBottom[2] = {
		{ 0.0f,360.0f,0.0f,1.0f },
		{ 640.0f,360.0f,0.0f,1.0f }
	};
	Vector4 RightTop[2] = {
		{ 640.0f,0.0f,0.0f,1.0f },
		{ 1280.0f,0.0f,0.0f,1.0f }

	};
	Vector4 RightBottom[2] = {
		{ 640.0f,360.0f,0.0f,1.0f },
		{ 1280.0f,360.0f,0.0f,1.0f }
	};


};