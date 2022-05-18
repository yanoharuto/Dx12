#pragma once
#include <d3d12.h>
#include <vector>
#pragma comment (lib,"d3d12.lib")
class RenderTargetView
{
private:
    std::vector<ID3D12Resource*> mBackBuffers;
public:
    RenderTargetView(int bufferCount);
    ~RenderTargetView();

    ID3D12Resource** GetBackBuffer(int idx) { return &mBackBuffers[idx]; };
    
};

