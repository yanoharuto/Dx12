#pragma once
#include <dxgi1_6.h>
#include "RenderTargetView.h"
#include "Descriptor.h"
#pragma comment(lib,"dxgi.lib")


class SwapChain
{
private:
    DXGI_SWAP_CHAIN_DESC1 mSwapChainDesc = {};
    
    RenderTargetView* mpRTV = nullptr;
    DescriptorsHeap* mpRTVDescriptor = nullptr;
    IDXGISwapChain4* mpIDXGISwapChain = nullptr;

    void InitRTV();
    void InitDescriptor(ID3D12Device* pDevice);
public:
    SwapChain();
    ~SwapChain();
    DXGI_SWAP_CHAIN_DESC1* GetSwapChainDesc() { return &mSwapChainDesc; }
    IDXGISwapChain4** GetDXGISwapChain() { return &mpIDXGISwapChain; }
    void Run();
    void Init(LONG WindowWidth,LONG WindowHeight,ID3D12Device* pDevice);
    void LinkingBufferToView(ID3D12Device* pDevice);
};

