#include "Application.h"

//面倒だけど書かなければいけない関数
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //ウィンドウが破棄されたら呼ばれる
    if (msg == WM_DESTROY)
    {
        PostQuitMessage(0);//OSに対して「もうこのアプリは終わる」と伝える
        return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

/// <summary>
/// コンソール画面にフォーマット付き文字列を表示
/// </summary>
/// <param name="format">フォーマット(%dとか%fとかの)</param>
/// <param name="">可変長引数</param>
/// <remarks> この関数はデバッグ用です。デバッグ時にしか動作しません
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
    mWindowClass.lpfnWndProc = (WNDPROC)WindowProcedure;//コールバック関数の指定
    mWindowClass.lpszClassName = TEXT("DX12Sample");//アプリケーションクラス名
    mWindowClass.hInstance = GetModuleHandle(nullptr);//ハンドルの所得

    RegisterClassEx(&mWindowClass);//アプリケーションクラス（ウィンドウクラスの指定をOSに伝える）

    RECT wrc = { 0,0,static_cast<LONG>(mWindow_Width),static_cast<LONG>(mWindow_Height) };//ウィンドウサイズを決める
    //関数を使ってウィンドウのサイズを補正する
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

    //ウィンドウオブジェクトの生成
    mHwnd = CreateWindow(
        mWindowClass.lpszClassName,//クラス名指定
        TEXT("DX12テスト"),        //タイトルバーの文字
        WS_OVERLAPPEDWINDOW,       //タイトルバーと境界線があるウィンドウ
        CW_USEDEFAULT,             //表示X座標はOSにお任せ
        CW_USEDEFAULT,             //表示Y座標はOSにお任せ
        wrc.right - wrc.left,      //ウィンドウ幅
        wrc.bottom - wrc.top,      //ウィンドウ高
        nullptr,                   //親ウィンドウハンドル
        nullptr,                   //メニューハンドル
        mWindowClass.hInstance,    //呼び出しアプリケーション
        nullptr);                  //追加パラメーター
}

void Application::InitFeatureLevel()
{
    //Direct3Dデバイスの初期化
    D3D_FEATURE_LEVEL featureLevel;

    for (auto lv : levels)
    {
        if (D3D12CreateDevice(nullptr, lv, IID_PPV_ARGS(&mpDevice)) == S_OK)
        {
            featureLevel = lv;
            break;//生成可能なバージョンが見つかったらループを打ち切り
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

    //アダプターの列挙用
    std::vector<IDXGIAdapter*> pAdapters;

    //ここに特定の名前を持つアダプターオブジェクトが入る
    IDXGIAdapter* tmpAdapter = nullptr;

    for (int i = 0; mpDxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
    {
        pAdapters.push_back(tmpAdapter);
    }
    for (auto adpt : pAdapters)
    {
        DXGI_ADAPTER_DESC adesc = {};
        adpt->GetDesc(&adesc);//アダプターの説明オブジェクト所得

        std::wstring strDesc = adesc.Description;

        //探したいアダプターの名前を確認
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
    //ウィンドウ表示
    ShowWindow(mHwnd, SW_SHOW);
    MSG msg = {};

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        //アプリケーションが終わるときにmessageがWM_QUITになる
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
