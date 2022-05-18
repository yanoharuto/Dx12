#include "Commanders.h"

void Commanders::Init(ID3D12Device* pDevice)
{
    auto result = pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mpCmdAllocator));
    result = pDevice->CreateCommandList(
        0, D3D12_COMMAND_LIST_TYPE_DIRECT,
        mpCmdAllocator, nullptr,
        IID_PPV_ARGS(&mpCmdList));
    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};

    //タイムアウトなし
    cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

    //アダプターを一つしか使わないときは0でよい
    cmdQueueDesc.NodeMask = 0;

    //プライオリティは特に指定なし
    cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

    //コマンドリストと合わせる
    cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    //キュー生成
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
