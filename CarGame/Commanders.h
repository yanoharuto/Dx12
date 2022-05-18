#pragma once

#include <d3d12.h>
#pragma comment (lib,"d3d12.lib")
class Commanders
{
private:
    
    ID3D12CommandAllocator* mpCmdAllocator = nullptr;
    ID3D12GraphicsCommandList* mpCmdList = nullptr;
    ID3D12CommandQueue* mpCmdQueue = nullptr;
    
public:
    Commanders();
    ~Commanders();
    
    void Run();
    void Close();
    void Init(ID3D12Device* pDevice);
    ID3D12CommandQueue* GetQueue() { return mpCmdQueue; };
};

