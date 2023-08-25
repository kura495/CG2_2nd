#pragma once
#include "DirectXCommon.h"
#include "Math_Structs.h"
#include <xaudio2.h>
#include <x3daudio.h>
#include <cassert>
#pragma comment(lib,"xaudio2.lib")
#pragma comment(lib, "winmm.lib")
#include <fstream>
#include <map>



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
	
	void Release();
	uint32_t LoadAudio(const char* filename);
	void Play(int AudioInDex, float AudioVolume, int pan);
	void SoundUnload(uint32_t Index);
private:
	XAudio2() = default;
	~XAudio2() = default;
	XAudio2(const XAudio2& obj) = delete;
	XAudio2& operator=(const XAudio2& obj) = delete;

	float left = 0;
	float right = 0;
	static const int kMaxAudio = 8;
	HRESULT hr;
	Microsoft::WRL::ComPtr<IXAudio2> XAudioInterface = nullptr;
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;
	//ソースボイス
	IXAudio2SourceVoice* pSourceVoice[kMaxAudio];
	bool IsusedAudioIndex[kMaxAudio];
	//音声データ
	//再生中にぶっ飛ばすとバグるぜ！！！
	std::map<uint32_t, SoundData> soundData_;

	float outputMatrix[8];

	SoundData SoundLoadWave(const char* filename);
	
	void Log(const std::string& message);
};

