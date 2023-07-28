#pragma once
#include "Base/DirectXCommon.h"
#include <xaudio2.h>
#include<x3daudio.h>
#include <mmsystem.h>
#include"includeStruct/Vector2.h"
#include<cassert>
#pragma comment(lib,"xaudio2.lib")
#pragma comment(lib, "winmm.lib")
#include<fstream>
struct ChunkHeader {
	char id[4];//チャンクID
	int32_t size;//チャンクサイズ
};
struct RiffHeader {
	ChunkHeader chunk;//"RIFF"
	char type[4];//"WAVE"
};
struct FormatChunk {
	ChunkHeader chunk;//"fmt "
	WAVEFORMATEX fmt;//フォーマット
};
struct SoundData {
	//波形フォーマット
	WAVEFORMATEX wfex;
	//バッファの先頭
	BYTE* pBuffer;
	//バッファのサイズ
	unsigned int bufferSize;
};
class XAudio2 {
public:
	static XAudio2* GetInstance();
	void Initialize();
	uint32_t LoadAudio(const wchar_t* filePath);
	void Release();
	void Play(int AudioInDex, float AudioVolume, int pan);

private:
	float left = 0;
	float right = 0;
	static const int kMaxAudio = 8;
	HRESULT hr;
	Microsoft::WRL::ComPtr<IXAudio2> XAudioInterface = nullptr;
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;
	IXAudio2SourceVoice* pSourceVoice[kMaxAudio];
	bool IsusedAudioIndex[kMaxAudio];
	float outputMatrix[8];
	void Log(const std::string& message);
};

