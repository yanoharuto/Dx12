#include "SwapChain.h"

void SwapChain::InitRTV()
{
    mpRTV = new RenderTargetView(mSwapChainDesc.BufferCount);
}

void SwapChain::InitDescriptor(ID3D12Device* pDevice)
{
    mpRTVDescriptor = new DescriptorsHeap();
    mpRTVDescriptor->InitHeapDesc();
    pDevice->CreateDescriptorHeap(
        mpRTVDescriptor->GetHeapDesc(),
        IID_PPV_ARGS(mpRTVDescriptor->GetDescriptorHeap())
    );
}

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
    delete mpRTVDescriptor;
    mpRTVDescriptor = nullptr;
    delete mpRTV;
    mpRTV = nullptr;
}

void SwapChain::Run()
{
}

void SwapChain::Init(LONG WindowWidth, LONG WindowHeight,ID3D12Device* pDevice)
{
    mSwapChainDesc.Width = WindowWidth;
    mSwapChainDesc.Height = WindowHeight;
    mSwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    mSwapChainDesc.Stereo = false;
    mSwapChainDesc.SampleDesc.Count = 1;
    mSwapChainDesc.SampleDesc.Quality = 0;
    mSwapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
    mSwapChainDesc.BufferCount = 2;
    //バックバッファーは伸び縮み可能
    mSwapChainDesc.Scaling = DXGI_SCALING_STRETCH;

    //フリップ後は速やかに破棄
    mSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    //特に指定なし
    mSwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

    //ウィンドウ⇔フルスクリーン切り替え可能
    mSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    InitRTV();
    InitDescriptor(pDevice);
}
/// <summary>
/// BackBufferとViewの紐づけ
/// </summary>
void SwapChain::LinkingBufferToView(ID3D12Device* pDevice)
{  
    
    mpRTVDescriptor->InitDescriptorHandle();
    for (int idx = 0; idx < mSwapChainDesc.BufferCount; ++idx)
    {
        auto result = mpIDXGISwapChain->GetBuffer(idx, IID_PPV_ARGS(mpRTV->GetBackBuffer(idx)));
        mpRTVDescriptor->SetHandlePtr( idx * pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
        pDevice->CreateRenderTargetView(*mpRTV->GetBackBuffer(idx),nullptr,mpRTVDescriptor->GetHandle());
    }   

}
