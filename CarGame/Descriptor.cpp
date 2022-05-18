#include "Descriptor.h"

DescriptorsHeap::DescriptorsHeap()
{
}

DescriptorsHeap::~DescriptorsHeap()
{
}

void DescriptorsHeap::InitHeapDesc()
{
    mHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�[�^�[�Q�b�g�r���[
    mHeapDesc.NodeMask = 0;//������Ȃ̂�0
    mHeapDesc.NumDescriptors = 2;//�\���̓��
    mHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//���Ɏw��Ȃ�
}

void DescriptorsHeap::InitDescriptorHandle()
{
    mDescriptorHandle = mDescriptorHeaps->GetCPUDescriptorHandleForHeapStart();
}
