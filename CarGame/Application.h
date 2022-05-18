#include <Windows.h>
#ifdef _DEBUG

#include "Commanders.h"
#include "SwapChain.h"
#include <d3d12sdklayers.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <iostream>
#include <vector>
#endif
#pragma comment (lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")


using namespace std;

class Application
{
private:
    const float mWindow_Width = 1080;
    const float mWindow_Height = 960;
    D3D_FEATURE_LEVEL levels[4] =
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };
    WNDCLASSEX mWindowClass = {};
    HWND       mHwnd = {};
    
    Commanders* mpCommanders = nullptr;
    SwapChain* mpSwapChain = nullptr;
    

    ID3D12Device* mpDevice = nullptr;
    IDXGIFactory6* mpDxgiFactory = nullptr;

    

    void DebugOutputFormatString(const char* format, ...);

    void InitWindowClass();
    void InitFeatureLevel();
    void CreateFactory();
    void InitAdapter();
    void CreateCommanders();
    void InitSwapChain();

    void Terminate();
    
public:
    Application();
    ~Application();

    void Run();

};