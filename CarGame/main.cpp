#include "Application.h"

#ifdef _DEBUG
int main()
{
#else
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
#endif
    Application* pApp = new Application();
    getchar();
    pApp->Run();
    delete pApp;
    return 0;
}