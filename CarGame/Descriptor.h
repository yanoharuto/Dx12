#pragma once
#include <d3d12.h>
#pragma comment (lib,"d3d12.lib")
class DescriptorsHeap
{
private:  
    D3D12_CPU_DESCRIPTOR_HANDLE mDescriptorHandle = {};

    D3D12_DESCRIPTOR_HEAP_DESC mHeapDesc = {};
    ID3D12DescriptorHeap* mDescriptorHeaps = nullptr;

public:
    DescriptorsHeap();
    ~DescriptorsHeap();
    void InitHeapDesc();
    void InitDescriptorHandle();
    void SetHandlePtr(int ptr) { mDescriptorHandle.ptr += ptr; };
    ID3D12DescriptorHeap** GetDescriptorHeap() { return &mDescriptorHeaps; };
    D3D12_DESCRIPTOR_HEAP_DESC* GetHeapDesc() { return &mHeapDesc; };
    D3D12_CPU_DESCRIPTOR_HANDLE GetHandle() { return mDescriptorHandle; };
};