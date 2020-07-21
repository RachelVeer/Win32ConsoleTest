#include <stdio.h>
#include <iostream>
#include <windows.h>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

int CALLBACK WinMain( HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow )
{
    AllocConsole();
    FILE* file = nullptr;
    freopen_s( &file, "CONIN$", "r", stdin );
    freopen_s( &file, "CONOUT$", "w", stdout );

    spdlog::info( "Hello, {}!", "World" );

    printf( "This is indeed working" );

    // Test window
    LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
    bool ReconnectIO( bool OpenNewConsole );
    MSG msg;
    HWND hwnd;
    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszClassName = "Window";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush( COLOR_3DFACE );
    wc.lpszMenuName = NULL;
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );

    RegisterClass( &wc );
    hwnd = CreateWindow( wc.lpszClassName, "Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 350, 250, NULL, NULL, hInstance, NULL );

    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );

    printf( "Entering GetMessage loop\n" );
    while (GetMessage( &msg, NULL, 0, 0 ))
    {
        DispatchMessage( &msg );
        spdlog::info( "Message detected!" );
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hwnd, msg, wParam, lParam );
}