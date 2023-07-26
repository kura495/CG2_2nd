#pragma once
#include<wrl.h>
#include<d3d12.h>
Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
