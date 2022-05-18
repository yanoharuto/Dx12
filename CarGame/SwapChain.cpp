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
    //�o�b�N�o�b�t�@�[�͐L�яk�݉\
    mSwapChainDesc.Scaling = DXGI_SCALING_STRETCH;

    //�t���b�v��͑��₩�ɔj��
    mSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    //���Ɏw��Ȃ�
    mSwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

    //�E�B���h�E�̃t���X�N���[���؂�ւ��\
    mSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    InitRTV();
    InitDescriptor(pDevice);
}
/// <summary>
/// BackBuffer��View�̕R�Â�
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
