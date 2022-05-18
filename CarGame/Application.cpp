#include "Application.h"

//�ʓ|�����Ǐ����Ȃ���΂����Ȃ��֐�
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //�E�B���h�E���j�����ꂽ��Ă΂��
    if (msg == WM_DESTROY)
    {
        PostQuitMessage(0);//OS�ɑ΂��āu�������̃A�v���͏I���v�Ɠ`����
        return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

/// <summary>
/// �R���\�[����ʂɃt�H�[�}�b�g�t���������\��
/// </summary>
/// <param name="format">�t�H�[�}�b�g(%d�Ƃ�%f�Ƃ���)</param>
/// <param name="">�ϒ�����</param>
/// <remarks> ���̊֐��̓f�o�b�O�p�ł��B�f�o�b�O���ɂ������삵�܂���
void Application::DebugOutputFormatString(const char* format, ...)
{
#ifdef _DEBUG
    va_list valist;
    va_start(valist, format);
    vprintf(format, valist);
    va_end(valist);
#endif
}

void Application::InitWindowClass()
{
    mWindowClass.cbSize = sizeof(WNDCLASSEX);
    mWindowClass.lpfnWndProc = (WNDPROC)WindowProcedure;//�R�[���o�b�N�֐��̎w��
    mWindowClass.lpszClassName = TEXT("DX12Sample");//�A�v���P�[�V�����N���X��
    mWindowClass.hInstance = GetModuleHandle(nullptr);//�n���h���̏���

    RegisterClassEx(&mWindowClass);//�A�v���P�[�V�����N���X�i�E�B���h�E�N���X�̎w���OS�ɓ`����j

    RECT wrc = { 0,0,static_cast<LONG>(mWindow_Width),static_cast<LONG>(mWindow_Height) };//�E�B���h�E�T�C�Y�����߂�
    //�֐����g���ăE�B���h�E�̃T�C�Y��␳����
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

    //�E�B���h�E�I�u�W�F�N�g�̐���
    mHwnd = CreateWindow(
        mWindowClass.lpszClassName,//�N���X���w��
        TEXT("DX12�e�X�g"),        //�^�C�g���o�[�̕���
        WS_OVERLAPPEDWINDOW,       //�^�C�g���o�[�Ƌ��E��������E�B���h�E
        CW_USEDEFAULT,             //�\��X���W��OS�ɂ��C��
        CW_USEDEFAULT,             //�\��Y���W��OS�ɂ��C��
        wrc.right - wrc.left,      //�E�B���h�E��
        wrc.bottom - wrc.top,      //�E�B���h�E��
        nullptr,                   //�e�E�B���h�E�n���h��
        nullptr,                   //���j���[�n���h��
        mWindowClass.hInstance,    //�Ăяo���A�v���P�[�V����
        nullptr);                  //�ǉ��p�����[�^�[
}

void Application::InitFeatureLevel()
{
    //Direct3D�f�o�C�X�̏�����
    D3D_FEATURE_LEVEL featureLevel;

    for (auto lv : levels)
    {
        if (D3D12CreateDevice(nullptr, lv, IID_PPV_ARGS(&mpDevice)) == S_OK)
        {
            featureLevel = lv;
            break;//�����\�ȃo�[�W���������������烋�[�v��ł��؂�
        }
    }
    D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&mpDevice));
}

void Application::CreateFactory()
{
    auto result = CreateDXGIFactory1(IID_PPV_ARGS(&mpDxgiFactory));
}

void Application::InitAdapter()
{

    //�A�_�v�^�[�̗񋓗p
    std::vector<IDXGIAdapter*> pAdapters;

    //�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
    IDXGIAdapter* tmpAdapter = nullptr;

    for (int i = 0; mpDxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
    {
        pAdapters.push_back(tmpAdapter);
    }
    for (auto adpt : pAdapters)
    {
        DXGI_ADAPTER_DESC adesc = {};
        adpt->GetDesc(&adesc);//�A�_�v�^�[�̐����I�u�W�F�N�g����

        std::wstring strDesc = adesc.Description;

        //�T�������A�_�v�^�[�̖��O���m�F
        if (strDesc.find(L"NVIDIA") != std::string::npos)
        {
            tmpAdapter = adpt;
            break;
        }
    }
}

void Application::CreateCommanders()
{
    int a = 0;
    mpCommanders = new Commanders();
    mpCommanders->Init(mpDevice);    
}

void Application::InitSwapChain()
{
    mpSwapChain = new SwapChain();
    mpSwapChain->Init(
        static_cast<LONG>(mWindow_Width),
        static_cast<LONG>(mWindow_Height),
        mpDevice);
    auto result = mpDxgiFactory->CreateSwapChainForHwnd(
        mpCommanders->GetQueue(),
        mHwnd,
        mpSwapChain->GetSwapChainDesc(),
        nullptr,
        nullptr,
        (IDXGISwapChain1**)mpSwapChain->GetDXGISwapChain());
    mpSwapChain->LinkingBufferToView(mpDevice);
}


Application::Application()
{
    DebugOutputFormatString("Show window test.");
    InitWindowClass();
    InitFeatureLevel();
    CreateFactory();
    InitAdapter();
    CreateCommanders();
    InitSwapChain();
    
}

Application::~Application()
{
    Terminate();
}


void Application::Run()
{
    //�E�B���h�E�\��
    ShowWindow(mHwnd, SW_SHOW);
    MSG msg = {};

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        //�A�v���P�[�V�������I���Ƃ���message��WM_QUIT�ɂȂ�
        if (msg.message == WM_QUIT)
        {
            break;
        }
    }
}

void Application::Terminate()
{
    UnregisterClass(mWindowClass.lpszClassName, mWindowClass.hInstance);
    delete mpCommanders;
    mpCommanders = nullptr;
    delete mpSwapChain;
    mpSwapChain = nullptr;
}
