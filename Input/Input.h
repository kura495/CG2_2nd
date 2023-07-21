#pragma once
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include<dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include<wrl.h>
#include"Base/WinApp.h"
#include<array>
class Input
{
public:
	static Input* GetInstance();
	void Initialize(WinApp* winApp_);
	void Update();

	const std::array<BYTE, 256>& GetAllKey()const { return key; }
	const std::array<BYTE, 256>& GetAllPreKey()const { return preKey; }
	/// <summary>
	/// 押した瞬間
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool pushKey(uint8_t keyNumber);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool pressKey(uint8_t keyNumber);

private:
	HRESULT hr;
	Microsoft::WRL::ComPtr<IDirectInput8>directInput = nullptr;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard = nullptr;
	std::array<BYTE, 256> key;
	std::array<BYTE, 256> preKey;

};

