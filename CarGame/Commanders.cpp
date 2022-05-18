#include "Commanders.h"

void Commanders::Init(ID3D12Device* pDevice)
{
    auto result = pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mpCmdAllocator));
    result = pDevice->CreateCommandList(
        0, D3D12_COMMAND_LIST_TYPE_DIRECT,
        mpCmdAllocator, nullptr,
        IID_PPV_ARGS(&mpCmdList));
    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};

    //�^�C���A�E�g�Ȃ�
    cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

    //�A�_�v�^�[��������g��Ȃ��Ƃ���0�ł悢
    cmdQueueDesc.NodeMask = 0;

    //�v���C�I���e�B�͓��Ɏw��Ȃ�
    cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

    //�R�}���h���X�g�ƍ��킹��
    cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    //�L���[����
    result = pDevice->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&mpCmdQueue));

}

Commanders::Commanders()
{
}

Commanders::~Commanders()
{
}

void Commanders::Run()
{
}

void Commanders::Close()
{
}
