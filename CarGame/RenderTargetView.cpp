#include "RenderTargetView.h"

RenderTargetView::RenderTargetView(int bufferCount)
{
    std::vector<ID3D12Resource*> backBuffers(bufferCount);
    mBackBuffers = backBuffers;
    
}

RenderTargetView::~RenderTargetView()
{
    
}

